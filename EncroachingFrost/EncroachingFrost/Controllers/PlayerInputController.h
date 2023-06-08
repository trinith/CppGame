#pragma once

#include <Game\ControllerBase.h>
#include <Input\InputManager.h>
#include <Models\PlayerModel.h>

#include <iostream>

class PlayerInputController : public GhettoEngine::ControllerBase
{
public:
	PlayerInputController(PlayerModel& model, const InputManager& inputManager)
		: _model{ model }
		, _inputManager{ inputManager }
	{
	}

protected:
	virtual void OnFixedUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		_model.Dir = { 0, 0 };

		const InputState& inputState = _inputManager.GetState();

		if (inputState.HasAction(Action::Left))
			_model.Dir.x -= 1;
		if (inputState.HasAction(Action::Right))
			_model.Dir.x += 1;
		if (inputState.HasAction(Action::Up))
			_model.Dir.y -= 1;
		if (inputState.HasAction(Action::Down))
			_model.Dir.y += 1;
	}

private:
	PlayerModel& _model;
	const InputManager& _inputManager;
};