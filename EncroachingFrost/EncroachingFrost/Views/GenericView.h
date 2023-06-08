#pragma once

#include <Game\ViewBase.h>

#include <functional>

/// <summary>
/// A generic view that just runs a std::function on call. Should not be used for heavy lifting.
/// </summary>
class GenericView : public GhettoEngine::ViewBase
{
public:
	using DrawHandler = std::function<void(const GhettoEngine::GameTime&)>;

public:
	GenericView(DrawHandler draw)
		: _draw{ draw }
	{
	}

	GenericView(DrawHandler preDraw, DrawHandler draw)
		: _preDraw{ preDraw }
		, _draw{ draw }
	{
	}

protected:
	virtual void OnPreDraw(const GhettoEngine::GameTime& gameTime) override
	{
		if (_preDraw)
			_preDraw(gameTime);
	}

	virtual void OnDraw(const GhettoEngine::GameTime& gameTime) override
	{
		if (_draw)
			_draw(gameTime);
	}

private:
	DrawHandler _preDraw;
	DrawHandler _draw;
};