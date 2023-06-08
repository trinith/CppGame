#pragma once

#include <Assets\SpriteSheet.h>
#include <Drawing\SpriteRenderer.h>
#include <Entities\PlayerEntity.h>
#include <Game\ViewBase.h>

#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\System\Vector2.hpp>

class PlayerTargetView : public GhettoEngine::ViewBase
{
private:
	struct Constants
	{
		struct Offsets
		{
			inline static const sf::Vector2f LowerLeft{ -4, -2 };
			inline static const sf::Vector2f LowerRight{ -4 - 8, -2 };
			inline static const sf::Vector2f UpperLeft{ -3, -4 };
			inline static const sf::Vector2f UpperRight{ -3 - 8 - 2, -4 };
		};

		struct Sprites
		{
			inline static const size_t SelectionLower = 14;
			inline static const size_t SelectionUpper = 13;
		};
	};

public:
	PlayerTargetView(sf::RenderTarget& renderTarget, const PlayerEntity& player, const Assets::SpriteSheet& spriteSheet)
		: _renderTarget{ renderTarget }
		, _player{ player }
		, _spriteSheet{ spriteSheet }
	{
	}

protected:
	virtual void OnDraw(const GhettoEngine::GameTime&) override
	{
		const PlayerModel& playerModel = _player.GetModel();

		if (playerModel.Target)
		{
			const IGameEntity& target = *playerModel.Target;

			sf::FloatRect bounds{ target.GetBounds().Position, target.GetBounds().Size };
			target.GetHitboxes().ApplyGroundHitbox(bounds);

			SpriteRenderer::SetTexture(_spriteSheet.GetTexture());
			SpriteRenderer::SetColour((&target == &_player) ? sf::Color{ 0, 255, 0, 128 } : sf::Color{ 255, 0, 0, 128 });
			
			SpriteRenderer::Draw(
				_renderTarget,
				sf::Vector2f{ bounds.left, bounds.top + bounds.height } + Constants::Offsets::LowerLeft,
				_spriteSheet.GetSprite(Constants::Sprites::SelectionLower)
			);

			SpriteRenderer::Draw(
				_renderTarget,
				sf::Vector2f{ bounds.left + bounds.width, bounds.top + bounds.height } + Constants::Offsets::LowerRight,
				_spriteSheet.GetSprite(Constants::Sprites::SelectionLower),
				true
			);

			SpriteRenderer::Draw(
				_renderTarget,
				sf::Vector2f{ bounds.left, bounds.top } + Constants::Offsets::UpperLeft,
				_spriteSheet.GetSprite(Constants::Sprites::SelectionUpper)
			);

			SpriteRenderer::Draw(
				_renderTarget,
				sf::Vector2f{ bounds.left + bounds.width, bounds.top } + Constants::Offsets::UpperRight,
				_spriteSheet.GetSprite(Constants::Sprites::SelectionUpper),
				true
			);
		}
	}

private:
	sf::RenderTarget& _renderTarget;
	const PlayerEntity& _player;
	const Assets::SpriteSheet& _spriteSheet;
};