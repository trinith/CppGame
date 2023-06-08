#pragma once

#include <Game\ControllerBase.h>
#include <Models\CombatTextItems.h>
#include <Models\PendingAbilityActions.h>

#include <iostream>

class PendingAbilityActionsController : public GhettoEngine::ControllerBase
{
public:
	PendingAbilityActionsController(PendingAbilityActions& pendingActions, CombatTextItems& combatTextItems)
		: _pendingActions{ pendingActions }
		, _combatTextItems{ combatTextItems }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime&) override
	{
		while (_pendingActions.Queue.size())
		{
			PendingAbilityAction& action = _pendingActions.Queue.front();

			const EntityAbility& ability = action.Ability;
			const EntityStats& sourceStats = action.Source.GetStats();
			EntityStats& targetStats = action.Target.GetStats();
			if (targetStats.CanBeDamaged)
			{
				const float abilityStrength = CalculateAbilityStrength(ability, sourceStats, targetStats);
				const float appliedStrength = (ability.Type == AbilityType::Harm && targetStats.CanLoseHealth)
					? abilityStrength
					: 0.f;

				targetStats.ModifyHealth(appliedStrength);

				std::cout << sourceStats.Name << "'s " << ability.Name << " successfully cast for " << abilityStrength << " " << ((ability.Type == AbilityType::Harm) ? "damage" : "healing") << ". ";
				std::cout << "Value applied to " << targetStats.Name << " was " << appliedStrength << "." << std::endl;

				_combatTextItems.emplace_back(std::to_string(abs(static_cast<int>(abilityStrength))), action.Target, ability.Type);
			}
			else
			{
				std::cout << sourceStats.Name << "'s " << ability.Name << " failed because " << targetStats.Name << " cannot be damaged." << std::endl;
			}

			_pendingActions.Queue.pop();
		}
	}

private:
	float CalculateAbilityStrength(const EntityAbility& ability, const EntityStats& sourceStats, const EntityStats& targetStats)
	{
		float baseAmount = ability.StrengthMultiplier * sourceStats.BaseStrength;
		baseAmount *= (ability.Type == AbilityType::Harm) ? -1.f : 1.f;

		/*	May do more here in the future...
				* Crit chance?
				* Modification based on target defense?
				* Random value within a range instead of a fixed value?
		*/

		return baseAmount;
	}

	PendingAbilityActions& _pendingActions;
	CombatTextItems& _combatTextItems;
};