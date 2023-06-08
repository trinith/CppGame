#pragma once

#include <Game\GameTime.h>
#include <vector>

struct EntityAnimation
{
public:
	EntityAnimation(const std::vector<size_t>& frames, float secondsPerFrame = 0.2f, size_t initialFrame = 0)
		: _frames{ frames }
		, _secondsPerFrame{ secondsPerFrame }
		, _initialFrame{ initialFrame }
	{
		Reset();
	}

	size_t GetCurrentFrame() const { return _frames[_currentFrame]; }

	void Update(const GhettoEngine::GameTime& gameTime)
	{
		_timeRemaining -= gameTime.ElapsedSeconds.count();
		if (_timeRemaining < 0)
		{
			++_currentFrame;
			if (_currentFrame >= _frames.size())
				_currentFrame = 0;

			_timeRemaining += _secondsPerFrame;
		}
	}

	void Reset()
	{
		_currentFrame = _initialFrame;
		_timeRemaining = _secondsPerFrame;
	}

private:
	std::vector<size_t> _frames;
	float _secondsPerFrame;
	size_t _initialFrame;

	size_t _currentFrame;
	float _timeRemaining;
};