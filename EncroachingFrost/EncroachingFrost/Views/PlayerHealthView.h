#pragma once

#include <Models\PlayerModel.h>
#include <Views\ProgressBarViewBase.h>

class PlayerHealthView : public ProgressBarViewBase
{
public:
	PlayerHealthView(sf::RenderTarget& renderTarget, const PlayerModel& playerModel)
		: ProgressBarViewBase{ renderTarget, Constants::Position, Constants::Size }
		, _playerModel{ playerModel }
	{
	}

	virtual float GetFillPercent() const override
	{
		return _playerModel.Stats.Health / _playerModel.Stats.MaxHealth;
	}

	virtual const sf::Color& GetFillColour() const override
	{
		return Constants::FillColour;
	}

private:
	struct Constants
	{
		inline static const sf::Vector2f Position{ 2, 2 };
		inline static const sf::Vector2f Size{ 150, 6 };
		inline static const sf::Color FillColour{ 255, 128, 128 };
	};

	const PlayerModel& _playerModel;

	sf::RectangleShape _rect;
};