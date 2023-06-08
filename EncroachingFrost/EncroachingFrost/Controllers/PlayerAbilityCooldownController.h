#pragma once

#include <Game\ControllerBase.h>
#include <Models\PlayerModel.h>

#include <iostream>

class PlayerAbilityCooldownController : public GhettoEngine::ControllerBase
{
public:
	PlayerAbilityCooldownController(PlayerModel& playerModel)
		: _playerModel{ playerModel }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		std::vector<AbilityId> doomedIds;

		for (auto& [id, timeRemaining] : _playerModel.AbilityCooldowns.Cooldowns)
		{
			timeRemaining -= gameTime.ElapsedSeconds.count();
			if (timeRemaining <= 0.f)
			{
				doomedIds.emplace_back(id);
			}
		}

		for (auto&& id : doomedIds)
		{
			_playerModel.AbilityCooldowns.Cooldowns.erase(id);
			std::cout << GlobalAbilityRegistry::Registry.GetAbility(id)->get().Name << " cooldown complete." << std::endl;
		}
	}

private:
	PlayerModel& _playerModel;
};