#pragma once

#include <Game\ControllerBase.h>
#include <Models\PlayerModel.h>

// GT_TODO: We might want to roll this into entity somehow.
class PlayerHealthController : public GhettoEngine::ControllerBase
{
public:
	PlayerHealthController(PlayerModel& playerModel)
		: _playerModel{ playerModel }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		if (_playerModel.Stats.Power && _playerModel.Stats.Power.value() <= 0.f)
			_playerModel.Stats.ModifyHealth(-PlayerModel::Constants::ColdHealthDrain * gameTime.ElapsedSeconds.count());
	}

private:
	PlayerModel& _playerModel;
};