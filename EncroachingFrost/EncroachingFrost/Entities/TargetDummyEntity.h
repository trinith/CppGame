#pragma once

#include <Entities\IGameEntity.h>
#include <Models\TargetDummyModel.h>

class TargetDummyEntity : public IGameEntity
{
public:
	TargetDummyEntity(const sf::Vector2f& position)
		: _model{ position }
	{
	}

	const TargetDummyModel& GetModel() const { return _model; }
	TargetDummyModel& GetModel() { return _model; }

	virtual const EntityBounds& GetBounds() const override { return _model.Bounds; }

	virtual const EntityStats& GetStats() const override { return _model.Stats; }
	virtual EntityStats& GetStats() override { return _model.Stats; }

	virtual const EntitySprites& GetSprites() const override { return _model.Sprites; }

	virtual const EntityHitboxes& GetHitboxes() const override { return _model.Hitboxes; }

private:
	TargetDummyModel _model;
};