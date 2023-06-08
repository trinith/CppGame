#pragma once

#include <Game\ControllerBase.h>
#include <Models\PlayerModel.h>

class PlayerMoveFinalizeController : public GhettoEngine::ControllerBase
{
public:
	PlayerMoveFinalizeController(PlayerModel& model)
		: _model{ model }
	{
	}

protected:
	virtual void OnFixedUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		_model.Bounds.Position = _model.NextPosition;
	}

private:
	PlayerModel& _model;
};