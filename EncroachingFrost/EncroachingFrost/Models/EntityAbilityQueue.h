#pragma once

#include <Models\AbilityRegistry.h>
#include <Models\EntityAbilities.h>
#include <Models\EntityAbilityCooldowns.h>

#include <queue>

struct AbilityQueueEntry
{
	AbilityId Id;
	float TimeRemaining{ 0.f };
};

struct EntityAbilityQueue
{
	float GCD = 0.f;
	std::queue<AbilityQueueEntry> Queue;

	// GT_TODO: Refactor this but we can return a string for now.
	std::optional<std::string> TryEnqueue(EntityAbilityCooldowns& activeCooldowns, AbilityId id)
	{
		const auto abilityRef = GlobalAbilityRegistry::Registry.GetAbility(id);
		if (!abilityRef)
			return "ability not found";

		if (GCD > Constants::QueueThreshold)
			return "GCD still active";

		if (Queue.size() > 0 && Queue.front().TimeRemaining > Constants::QueueThreshold)
			return "another cast currently in progress";

		if (activeCooldowns.IsCooldownActive(id))
			return "ability is on CD";

		const EntityAbility& ability = abilityRef->get();
		Queue.push(AbilityQueueEntry{ id , (ability.CastTime) ? ability.CastTime.value() : 0.f });
		GCD += Constants::GCD;

		return std::nullopt;
	}

	void CancelCurrentAction()
	{
		if (Queue.size() > 0)
		{
			Queue.pop();
			GCD -= Constants::GCD;

			if (GCD < 0)
				GCD = 0;
		}
	}

	struct Constants
	{
		inline static const float GCD = 1.5f;
		inline static const float QueueThreshold = 0.25f;
	};
};