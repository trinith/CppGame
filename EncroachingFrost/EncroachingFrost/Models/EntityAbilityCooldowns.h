#pragma once

#include <Models\AbilityRegistry.h>
#include <Models\EntityAbilities.h>
#include <unordered_map>

struct EntityAbilityCooldowns
{
	std::unordered_map<AbilityId, float> Cooldowns;

	bool IsCooldownActive(AbilityId id)
	{
		return Cooldowns.find(id) != Cooldowns.end();
	}
};