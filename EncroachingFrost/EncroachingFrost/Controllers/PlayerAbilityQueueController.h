#pragma once

#include <Entities\PlayerEntity.h>
#include <Game\ControllerBase.h>
#include <Models\PendingAbilityActions.h>

#include <iostream>

class PlayerAbilityQueueController : public GhettoEngine::ControllerBase
{
public:
	PlayerAbilityQueueController(PlayerEntity& playerEntity, PendingAbilityActions& pendingActions)
		: _playerEntity{ playerEntity }
		, _pendingActions{ pendingActions }
		, _playerModel{ playerEntity.GetModel() }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		EntityAbilityQueue& abilityQueue = _playerModel.AbilityQueue;
		abilityQueue.GCD -= gameTime.ElapsedSeconds.count();
		if (abilityQueue.GCD < 0.f)
			abilityQueue.GCD = 0.f;

		if (abilityQueue.Queue.size() > 0)
		{
			AbilityQueueEntry& entry = abilityQueue.Queue.front();
			entry.TimeRemaining -= gameTime.ElapsedSeconds.count();
			if (entry.TimeRemaining < 0.f)
			{
				if (const auto abilityRef = GlobalAbilityRegistry::Registry.GetAbility(entry.Id))
				{
					const EntityAbility& ability = *abilityRef;

					if (ability.Cost && _playerModel.Stats.Power && ability.Cost.value() > _playerModel.Stats.Power.value())
					{
						std::cout << "Could not activate " << ability.Name << ", not enough power." << std::endl;
						abilityQueue.CancelCurrentAction();
					}
					else
					{
						// Activate the ability.
						if (_playerModel.Target)
						{
							// Deduct the cost, if applicable.
							if (_playerModel.Stats.Power && ability.Cost)
								_playerModel.Stats.ModifyPower(-ability.Cost.value());

							_pendingActions.Enqueue(ability, _playerEntity, *_playerModel.Target);
							std::cout << "Activating: " << ability.Name << "." << std::endl;
						}
						else
						{
							std::cout << "Could not activate " << ability.Name << ", no target." << std::endl;
						}

						// Place the ability on cooldown
						if (ability.Cooldown)
							_playerModel.AbilityCooldowns.Cooldowns.emplace(entry.Id, ability.Cooldown.value());

						abilityQueue.Queue.pop();
					}
				}
			}
		}
	}

private:
	PlayerEntity& _playerEntity;
	PendingAbilityActions& _pendingActions;

	PlayerModel& _playerModel;
};