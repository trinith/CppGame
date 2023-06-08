#pragma once

#include <Entities\IGameEntity.h>
#include <Models\EntityAbilities.h>
#include <queue>

struct PendingAbilityAction
{
	const EntityAbility& Ability;
	IGameEntity& Source;
	IGameEntity& Target;
};

struct PendingAbilityActions
{
	std::queue<PendingAbilityAction> Queue;

	void Enqueue(const EntityAbility& ability, IGameEntity& source, IGameEntity& target)
	{
		Queue.push(PendingAbilityAction{ ability, source, target });
	}
};