#pragma once

#include <Game\ControllerBase.h>
#include <Models\CombatTextItems.h>

class CombatTextController : public GhettoEngine::ControllerBase
{
public:
	CombatTextController(CombatTextItems& combatTextItems)
		: _combatTextItems{ combatTextItems }
	{
	}

protected:
	virtual void OnFixedUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		for (size_t i = 0; i < _combatTextItems.size(); ++i)
		{
			CombatTextItem& item = _combatTextItems[i];

			item.TimeRemaining -= gameTime.ElapsedSeconds.count();
			if (item.TimeRemaining <= 0.f)
			{
				_combatTextItems.erase(_combatTextItems.begin() + i);
				--i;
				continue;
			}

			item.Offset += item.Dir * item.Speed * gameTime.ElapsedSeconds.count();
		}
	}

private:
	CombatTextItems& _combatTextItems;
};