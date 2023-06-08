#pragma once

#include <Entities\PlayerEntity.h>
#include <Game\ControllerBase.h>
#include <Input\InputManager.h>
#include <Models\AbilityRegistry.h>

#include <iostream>

class PlayerSkillActivationController : public GhettoEngine::ControllerBase
{
public:
	PlayerSkillActivationController(const InputManager& inputManager, PlayerEntity& playerEntity)
		: _inputManager{ inputManager }
		, _playerEntity{ playerEntity }
	{
	}

protected:
	virtual void OnFixedUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		const InputState& currentState = _inputManager.GetState();

		PlayerModel& playerModel = _playerEntity.GetModel();

		for (size_t actionValue = static_cast<size_t>(Constants::SlotStart); actionValue <= static_cast<size_t>(Constants::SlotEnd); ++actionValue)
		{
			const Action action = static_cast<Action>(actionValue);
			if (currentState.HasAction(action) && !_previousState.HasAction(action))
			{
				size_t actionIndex = actionValue - static_cast<size_t>(Constants::SlotStart);
				if (actionIndex >= 0 && actionIndex < playerModel.Abilities.size())
				{
					AbilityId id = playerModel.Abilities[actionIndex];
					if (id == AbilityId::Empty)
						continue;

					// If we don't have a target and it's a help ability, target self.
					const EntityAbility& ability = GlobalAbilityRegistry::Registry.GetAbility(id)->get();
					if (!playerModel.Target && ability.Type == AbilityType::Help)
						playerModel.Target = _playerEntity;

					// Check if we have a valid target.
					bool validTarget = true;
					if (playerModel.Target)
					{
						const IGameEntity& targetEntity = playerModel.Target.value();
						validTarget = (&targetEntity == &_playerEntity && ability.Type == AbilityType::Help)
							|| (&targetEntity != &_playerEntity && ability.Type == AbilityType::Harm);
					}
					else
					{
						validTarget = false;
					}

					if (!validTarget)
					{
						std::cout << "Invalid target!" << std::endl;
						continue;
					}

					// Check if we have enough resource to cast.
					if (ability.Cost && playerModel.Stats.Power < ability.Cost.value())
					{
						std::cout << "Could not initiate " << ability.Name << " cast, not enough power." << std::endl;
						continue;
					}

					// Queue the ability and check for an error message.
					if (std::optional<std::string> error = playerModel.AbilityQueue.TryEnqueue(playerModel.AbilityCooldowns, id))
					{
						std::cout << "Could not queue ability: " << error.value() << std::endl;
					}
					else
					{
						std::cout << "Successfully queued ability." << std::endl;
					}
				}
			}
		}

		_previousState = currentState;
	}

private:
	struct Constants
	{
		inline static const Action SlotStart = Action::SkillSlot1;
		inline static const Action SlotEnd = Action::SkillSlot5;
	};

	const InputManager& _inputManager;
	PlayerEntity& _playerEntity;

	InputState _previousState;
};