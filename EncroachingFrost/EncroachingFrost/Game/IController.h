#pragma once

#include <Game\GameTime.h>

namespace GhettoEngine
{

	class IController
	{
	public:
		virtual ~IController() = default;
		virtual void FixedUpdate(const GameTime& gameTime) = 0;
		virtual void Update(const GameTime& gameTime) = 0;
	};

}