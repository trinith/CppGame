#pragma once

#include <Models\PlayerModel.h>
#include <Views\ProgressBarViewBase.h>

class PlayerPowerView : public ProgressBarViewBase
{
public:
	PlayerPowerView(sf::RenderTarget& renderTarget, const PlayerModel& playerModel)
		: ProgressBarViewBase{ renderTarget, Constants::Position, Constants::Size }
		, _playerModel{ playerModel }
	{
	}

	virtual float GetFillPercent() const override
	{
		return (_playerModel.Stats.Power)
			? _playerModel.Stats.Power.value() / PlayerModel::Constants::MaxPower
			: 0.f;
	}

	virtual const sf::Color& GetFillColour() const override
	{
		float p = GetFillPercent();

		size_t count = Constants::FillColours.size() - 1;
		float indexPercent = p * (Constants::FillColours.size() - 1);
		size_t indexMin = static_cast<size_t>(indexPercent);
		size_t indexMax = std::clamp<size_t>(indexMin + 1, 0, count);
		float weight = (indexPercent - indexMin);

		if (indexMin == indexMax)
		{
			return Constants::FillColours[indexMin];
		}
		else
		{
			const sf::Color& minColour = Constants::FillColours[indexMin];
			const sf::Color& maxColour = Constants::FillColours[indexMax];

			float newR = minColour.r + (maxColour.r - minColour.r) * weight;
			float newG = minColour.g + (maxColour.g - minColour.g) * weight;
			float newB = minColour.b + (maxColour.b - minColour.b) * weight;

			return sf::Color{ static_cast<sf::Uint8>(newR), static_cast<sf::Uint8>(newG), static_cast<sf::Uint8>(newB) };
		}
	}

private:
	struct Constants
	{
		inline static const sf::Vector2f Position{ 2, 7 };
		inline static const sf::Vector2f Size{ 100, 6 };
		inline static const std::vector<sf::Color> FillColours
		{
			sf::Color{96, 0, 0},
			sf::Color{255, 0, 0},
			sf::Color{255, 196, 0},
			sf::Color{255, 255, 0},
			sf::Color{255, 255, 255},
		};
	};

	const PlayerModel& _playerModel;

	sf::RectangleShape _rect;
};