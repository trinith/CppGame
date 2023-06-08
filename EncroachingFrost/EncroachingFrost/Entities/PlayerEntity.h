#pragma once

#include <Entities\IGameEntity.h>
#include <Models\PlayerModel.h>

class PlayerEntity : public IGameEntity
{
public:
	PlayerEntity()
		: _model{}
	{
	}

	const PlayerModel& GetModel() const { return _model; }
	PlayerModel& GetModel() { return _model; }

	virtual const EntityBounds& GetBounds() const override { return _model.Bounds; }

	virtual const EntityStats& GetStats() const override { return _model.Stats; }
	virtual EntityStats& GetStats() override { return _model.Stats; }

	virtual const EntitySprites& GetSprites() const override { return _model.Sprites; }

	virtual const EntityHitboxes& GetHitboxes() const override { return _model.Hitboxes; }

private:
	PlayerModel _model;
};