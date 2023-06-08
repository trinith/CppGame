#pragma once

#include <Game\ControllerBase.h>
#include <Models\PlayerModel.h>

#include <iostream>

class PlayerMoveAbilityCancelController : public GhettoEngine::ControllerBase
{
public:
	PlayerMoveAbilityCancelController(PlayerModel& playerModel)
		: _playerModel{ playerModel }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime&) override
	{
		if (_playerModel.AbilityQueue.Queue.size() > 0 && (_playerModel.Dir.x != 0 || _playerModel.Dir.y != 0))
		{
			const AbilityId id = _playerModel.AbilityQueue.Queue.front().Id;

			// An ability is in progress and the player is moving. Cancel it.
			if (auto abilityRef = GlobalAbilityRegistry::Registry.GetAbility(id))
			{
				const EntityAbility& ability = *abilityRef;

				if (ability.CastTime)
					_playerModel.AbilityQueue.CancelCurrentAction();

				std::cout << ability.Name << " cast cancelled due to movement." << std::endl;
			}
		}
	}

private:
	PlayerModel& _playerModel;
};