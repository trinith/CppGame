#pragma once

#include <Models\PlayerModel.h>
#include <Views\ProgressBarViewBase.h>

class PlayerAbilityCastView : public ProgressBarViewBase
{
public:
	PlayerAbilityCastView(sf::RenderTarget& renderTarget, const PlayerModel& playerModel)
		: ProgressBarViewBase{ renderTarget, Constants::Position, Constants::Size }
		, _playerModel{ playerModel }
	{
	}

	virtual float GetFillPercent() const override
	{
		if (_playerModel.AbilityQueue.Queue.size() > 0)
		{
			float p = 0.f;
			const AbilityQueueEntry& entry = _playerModel.AbilityQueue.Queue.front();
			if (auto abilityRef = GlobalAbilityRegistry::Registry.GetAbility(entry.Id))
			{
				const EntityAbility& ability = *abilityRef;
				if (ability.CastTime)
					p = 1.f - entry.TimeRemaining / ability.CastTime.value();
			}

			return p;
		}
		else
		{
			return 0.0f;
		}
	}

	virtual const sf::Color& GetFillColour() const override
	{
		return Constants::FillColour;
	}

	virtual bool IsVisible() const override
	{
		return _playerModel.AbilityQueue.Queue.size() > 0;
	}

private:
	struct Constants
	{
		inline static const sf::Vector2f Position{ 101, 7 };
		inline static const sf::Vector2f Size{ 51, 6 };
		inline static const sf::Color FillColour{ 0, 210, 255 };
	};

	const PlayerModel& _playerModel;
};