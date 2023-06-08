#pragma once

#include <Game\ControllerBase.h>
#include <Input\InputManager.h>
#include <Models\PlayerUseInputModel.h>
#include <Models\RenderCanvas.h>

class PlayerUseInputController : public GhettoEngine::ControllerBase
{
public:
	PlayerUseInputController(PlayerUseInputModel& model, const InputManager& inputManager, const RenderCanvas& canvas)
		: _model{ model }
		, _inputManager{ inputManager }
		, _canvas{ canvas }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime&) override
	{
		const bool useAction = _inputManager.GetState().HasAction(Action::PrimaryUse);

		if (_lastUseAction && !useAction)
			_model.worldPosition = _canvas.ScreenToWorld(_inputManager.GetMousePosition());
		else
			_model.worldPosition = std::nullopt;

		_lastUseAction = useAction;
	}

private:
	PlayerUseInputModel& _model;
	const InputManager& _inputManager;
	const RenderCanvas& _canvas;

	bool _lastUseAction = false;
};