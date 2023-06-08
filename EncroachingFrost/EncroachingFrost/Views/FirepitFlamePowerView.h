#pragma once

#include <Game\ViewBase.h>
#include <Entities\FirepitFlameEntity.h>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <vector>

class FirepitFlamePowerView : public GhettoEngine::ViewBase
{
public:
	FirepitFlamePowerView(sf::RenderTarget& renderTarget, const std::vector<FirepitFlameEntity>& flames)
		: _renderTarget{ renderTarget }
		, _flames{ flames }
	{
	}

protected:
	virtual void OnDraw(const GhettoEngine::GameTime& gameTime) override
	{
		for (auto&& flameEntity : _flames)
		{
			const FirepitFlameModel& flame{ flameEntity.GetModel() };

			if (!flame.Stats.Power)
				continue;

			if (flame.Stats.Power.value() < FirepitFlameModel::Constants::MaxPower)
			{

				_rect.setPosition(flame.Bounds.Position + sf::Vector2f{ 0, -Constants::BarHeight + Constants::BarOffsetY });
				_rect.setSize(sf::Vector2f{ flame.Bounds.Size.x, Constants::BarHeight });
				_rect.setOutlineThickness(-1);
				_rect.setOutlineColor(sf::Color::Black);
				_rect.setFillColor(sf::Color{ 128, 128, 128 });
				_renderTarget.draw(_rect);

				_rect.setPosition(_rect.getPosition() + sf::Vector2f{ 1, 1 });
				_rect.setSize(_rect.getSize() + sf::Vector2f{ -2, -2 });
				_rect.setSize(sf::Vector2f{ _rect.getSize().x * flame.Stats.Power.value() / FirepitFlameModel::Constants::MaxPower, _rect.getSize().y });
				_rect.setFillColor(sf::Color::White);
				_rect.setOutlineThickness(0);
				_renderTarget.draw(_rect);
			}
		}
	}

private:
	struct Constants
	{
		inline static const float BarHeight = 4.f;
		inline static const float BarOffsetY = -1.f;
	};

	sf::RenderTarget& _renderTarget;
	const std::vector<FirepitFlameEntity>& _flames;

	sf::RectangleShape _rect;
};