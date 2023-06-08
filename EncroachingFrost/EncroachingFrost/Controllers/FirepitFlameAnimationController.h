#pragma once

#include <Entities\FirepitFlameEntity.h>
#include <Game\ControllerBase.h>
#include <vector>

struct FirepitFlamesAnimationController : public GhettoEngine::ControllerBase
{
public:
	FirepitFlamesAnimationController(std::vector<FirepitFlameEntity>& flames)
		: _flames{ flames }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		for (auto&& flameEntity : _flames)
		{
			FirepitFlameModel& flame = flameEntity.GetModel();

			if (!flame.Stats.Power)
				continue;

			flame.Animation.Update(gameTime);
			flame.Sprites.Main = flame.Animation.GetCurrentFrame();

			// Modify the alpha level of the sprite based on its power.
			// This could probably go in another controller but meh, it's close enough!
			const float p = flame.Stats.Power.value() / FirepitFlameModel::Constants::MaxPower;
			if (p < Constants::PowerThreshold)
			{
				float newAlpha = std::clamp(
					Constants::MinAlpha + (Constants::MaxAlpha - Constants::MinAlpha) * (p / Constants::PowerThreshold),
					Constants::MinAlpha,
					Constants::MaxAlpha
				);
				flame.Sprites.MainAlpha = static_cast<sf::Uint8>(newAlpha);
			}
			else
			{
				flame.Sprites.MainAlpha = 255;
			}
		}
	}

private:
	struct Constants
	{
		inline static const float MinAlpha = 32;
		inline static const float MaxAlpha = 255;
		inline static const float PowerThreshold = 0.8f;
	};

	std::vector<FirepitFlameEntity>& _flames;
};