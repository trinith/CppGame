#pragma once

#include <Assets\AssetLoader.h>
#include <Drawing\SpriteRenderer.h>
#include <Game\ViewBase.h>
#include <Models\AbilityIconMap.h>
#include <Models\RenderCanvas.h>
#include <Models\EntityAbilityCooldowns.h>
#include <Models\EntityAbilityQueue.h>
#include <Models\PlayerModel.h>

class PlayeAbilityInterfaceView : public GhettoEngine::ViewBase
{
public:
	PlayeAbilityInterfaceView(
		RenderCanvas& canvas,
		const PlayerModel& playerModel,
		const Assets::SpriteSheet& spriteSheet,
		const EntityAbilityQueue& abilityQueue,
		const EntityAbilityCooldowns& abilityCooldowns,
		const const Assets::AssetManager::Fonts& fonts
	)
		: _canvas{ canvas }
		, _playerModel{ playerModel }
		, _spriteSheet{ spriteSheet }
		, _abilityQueue{ abilityQueue }
		, _abilityCooldowns{ abilityCooldowns }
	{
		// Size is 16 times the number of icons, plus one pixel of space in between each.
		const sf::Vector2f size = sf::Vector2f
		{
			_playerModel.Abilities.size() * Constants::IconSize.x + (_playerModel.Abilities.size() - 1),
			Constants::IconSize.y
		};
		_frameRect.setSize(size);

		// Centre the bar over the canvas, three pixels up from the bottom of the screen.
		const sf::Vector2f worldSize{ _canvas.GetWorldSize() };
		const sf::Vector2f position = sf::Vector2f{
			worldSize.x / 2.f - size.x / 2.f,
			worldSize.y - size.y - 3.f
		};
		_frameRect.setPosition(static_cast<sf::Vector2f>(static_cast<sf::Vector2i>(position)));

		// Set bar frame properties.
		_frameRect.setOutlineColor(sf::Color::Black);
		_frameRect.setFillColor(Constants::Colours::Background);
		_frameRect.setOutlineColor(Constants::Colours::Outline);
		_frameRect.setOutlineThickness(1.f);

		// Set seperator line properties
		_sepRect.setSize(sf::Vector2f{ 1.f, Constants::IconSize.y });
		_sepRect.setOutlineThickness(0);
		_sepRect.setFillColor(Constants::Colours::Outline);

		// Text properties
		auto font = fonts[Assets::Fonts::CombatText];
		ASSERT(font);
		_text.setFont(font->get());
		_text.setCharacterSize(5);
		_text.setFillColor(sf::Color::White);
		_text.setOutlineColor(sf::Color::Black);
		_text.setOutlineThickness(1.f);
	}

protected:
	virtual void OnDraw(const GhettoEngine::GameTime&) override
	{
		sf::RenderTarget& target = _canvas.GetTarget();
		target.draw(_frameRect);

		sf::Vector2f pos = _frameRect.getPosition();
		size_t index = 1;
		for (auto&& id : _playerModel.Abilities)
		{
			if (const auto abilityRef = GlobalAbilityRegistry::Registry.GetAbility(id))
			{
				const EntityAbility& ability = *abilityRef;

				// Draw Icon
				if (std::optional<size_t> abilityIcon = AbilityIconMap::GetIcon(id))
				{
					SpriteRenderer::SetTexture(_spriteSheet.GetTexture());
					SpriteRenderer::DrawOutline(target, pos, _spriteSheet.GetSprite(abilityIcon.value()));
				}

				// Draw info overlay
				_overlayRect.setFillColor(Constants::Colours::Empty);

				if (_playerModel.Target)
				{
					sf::FloatRect playerRect{ _playerModel.Bounds.Position, _playerModel.Bounds.Size };
					_playerModel.Hitboxes.ApplySpriteHitbox(playerRect);
					sf::Vector2f playerCentre{ playerRect.left + playerRect.width / 2.f, playerRect.top + playerRect.height / 2.f };

					const IGameEntity& targetEntity = *_playerModel.Target;
					sf::FloatRect targetRect{ targetEntity.GetBounds().Position, targetEntity.GetBounds().Size };
					targetEntity.GetHitboxes().ApplySpriteHitbox(targetRect);
					sf::Vector2f targetCentre{ targetRect.left + targetRect.width / 2.f, targetRect.top + targetRect.height / 2.f };

					const float distSquared = VectorLengthSquared(targetCentre - playerCentre);
					if (distSquared > ability.Range * ability.Range)
						_overlayRect.setFillColor(Constants::Colours::OverlayNoRange);
				}

				if (_overlayRect.getFillColor() == Constants::Colours::Empty && ability.Cost && _playerModel.Stats.Power && ability.Cost.value() > _playerModel.Stats.Power.value())
					_overlayRect.setFillColor(Constants::Colours::OverlayNoPower);

				if (_overlayRect.getFillColor() != Constants::Colours::Empty)
				{
					_overlayRect.setSize(sf::Vector2f{ Constants::IconSize.x, Constants::IconSize.y });
					_overlayRect.setPosition(sf::Vector2f{ pos.x, pos.y });
					target.draw(_overlayRect);
				}

				// Draw CD overlay
				_overlayRect.setFillColor(Constants::Colours::OverlayOnCD);

				std::optional<float> fillPercent;
				if (const auto findResult = _abilityCooldowns.Cooldowns.find(id); findResult != _abilityCooldowns.Cooldowns.end())
				{
					// Ability is on CD
					if (ability.Cooldown)
						fillPercent = findResult->second / ability.Cooldown.value();
				}

				if (!fillPercent)
					fillPercent = _abilityQueue.GCD / EntityAbilityQueue::Constants::GCD;

				_overlayRect.setSize(sf::Vector2f{ Constants::IconSize.x, Constants::IconSize.y * fillPercent.value() });
				_overlayRect.setPosition(sf::Vector2f{ pos.x, pos.y + _frameRect.getSize().y - _overlayRect.getSize().y });
				target.draw(_overlayRect);
			}

			// Draw text
			_text.setString(std::to_string(index));
			_text.setPosition(pos + sf::Vector2f{ 1.f, 0.f });
			target.draw(_text);
			index++;

			// Draw seperator
			pos.x += Constants::IconSize.x;
			_sepRect.setPosition(pos);
			target.draw(_sepRect);
			pos.x += 1;
		}
	}

private:
	struct Constants
	{
		inline static const sf::Vector2f IconSize{ 16.f, 16.f };

		struct Colours
		{
			inline static const sf::Color Empty{ 0, 0, 0, 0 };
			inline static const sf::Color Outline{ 0, 0, 0 };
			inline static const sf::Color Background{ 64, 64, 64 };
			inline static const sf::Color OverlayOnCD{ 0, 0, 0, 96 };
			inline static const sf::Color OverlayNoPower{ 64, 64, 128, 96 };
			inline static const sf::Color OverlayNoRange{ 128, 32, 32, 96 };
		};
	};

	RenderCanvas& _canvas;
	const PlayerModel& _playerModel;
	const Assets::SpriteSheet& _spriteSheet;
	const EntityAbilityQueue& _abilityQueue;
	const EntityAbilityCooldowns& _abilityCooldowns;

	sf::RectangleShape _frameRect;
	sf::RectangleShape _sepRect;
	sf::RectangleShape _overlayRect;
	sf::Text _text;
};