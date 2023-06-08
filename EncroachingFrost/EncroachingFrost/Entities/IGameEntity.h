#pragma once

#include <Models\EntityBounds.h>
#include <Models\EntityHitboxes.h>
#include <Models\EntitySprites.h>
#include <Models\EntityStats.h>

class IGameEntity
{
public:
	virtual ~IGameEntity() = default;
	virtual const EntityBounds& GetBounds() const = 0;
	virtual const EntitySprites& GetSprites() const = 0;
	virtual const EntityHitboxes& GetHitboxes() const = 0;
	
	virtual const EntityStats& GetStats() const = 0;
	virtual EntityStats& GetStats() = 0;
};