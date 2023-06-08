#pragma once

#include <Assets\AssetManager.h>
#include <Game\ViewBase.h>
#include <Models\EntityAbilities.h>
#include <Models\CombatTextItems.h>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

class CombatTextView : public GhettoEngine::ViewBase
{
public:
	CombatTextView(sf::RenderTarget& renderTarget, const CombatTextItems& combatTextItems, const Assets::AssetManager::Fonts& fonts)
		: _renderTarget{ renderTarget }
		, _combatTextItems{ combatTextItems }
		, _text{}
	{
		const auto font = fonts[Assets::Fonts::CombatText];
		ASSERT(font);

		_text.setFont(font->get());
		_text.setOutlineColor(sf::Color::Black);
		_text.setOutlineThickness(1);
	}

protected:
	virtual void OnDraw(const GhettoEngine::GameTime&) override
	{
		for (auto&& item : _combatTextItems)
		{
			const IGameEntity& target = item.Target.get();

			_text.setCharacterSize(7);
			_text.setString(item.Text);
			const sf::Vector2f pos{ target.GetBounds().Position + item.Offset + sf::Vector2f{0, -_text.getGlobalBounds().height} };
			_text.setFillColor(item.Type == AbilityType::Help ? sf::Color::Green : sf::Color::Red);
			_text.setPosition(static_cast<sf::Vector2f>(static_cast<sf::Vector2i>(pos)));
			_renderTarget.draw(_text);
		}
	}

private:
	sf::RenderTarget& _renderTarget;
	const CombatTextItems& _combatTextItems;

	sf::Text _text;
};