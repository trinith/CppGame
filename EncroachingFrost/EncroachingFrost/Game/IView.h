#pragma once

#include <Game\GameTime.h>

namespace GhettoEngine
{

	class IView
	{
	public:
		virtual ~IView() = default;
		virtual void PreDraw(const GameTime& gameTime) = 0;
		virtual void Draw(const GameTime& gameTime) = 0;
	};

}