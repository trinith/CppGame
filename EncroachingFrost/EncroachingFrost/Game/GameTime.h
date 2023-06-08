#pragma once

#include <chrono>

namespace GhettoEngine
{

	struct GameTime
	{
		std::chrono::duration<float> ElapsedSeconds;
	};

}