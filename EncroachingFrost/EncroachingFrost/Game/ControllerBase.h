#pragma once

#include <Game\IController.h>

namespace GhettoEngine
{

	class ControllerBase : public IController
	{
	public:
		virtual void FixedUpdate(const GameTime& gameTime) final
		{
			OnFixedUpdate(gameTime);
		}

		virtual void Update(const GameTime& gameTime) final
		{
			OnUpdate(gameTime);
		}

	protected:
		virtual void OnFixedUpdate(const GameTime& gameTime) { }
		virtual void OnUpdate(const GameTime& gameTime) { }
	};

}