#pragma once

#include <Entities\IGameEntity.h>
#include <Models\FirepitFlameModel.h>

struct FirepitFlameEntity : public IGameEntity
{
public:
	FirepitFlameEntity(const sf::Vector2f& position)
		: _model{ position }
	{
	}

	const FirepitFlameModel& GetModel() const { return _model; }
	FirepitFlameModel& GetModel() { return _model; }

	virtual const EntityBounds& GetBounds() const override { return _model.Bounds; }

	virtual const EntityStats& GetStats() const override { return _model.Stats; }
	virtual EntityStats& GetStats() override { return _model.Stats; }

	virtual const EntitySprites& GetSprites() const override { return _model.Sprites; }

	virtual const EntityHitboxes& GetHitboxes() const override { return _model.Hitboxes; }

private:
	FirepitFlameModel _model;
};