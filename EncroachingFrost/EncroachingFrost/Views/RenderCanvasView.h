#pragma once

#include <WindowManager.h>
#include <Game\ViewBase.h>
#include <Models\RenderCanvas.h>

class RenderCanvasView : public GhettoEngine::ViewBase
{
public:
	RenderCanvasView(const RenderCanvas& canvas, WindowManager::Window& window)
		: _canvas{ canvas }
		, _window{ window }
	{
	}

protected:
	virtual void OnDraw(const GhettoEngine::GameTime& gameTime) override
	{
		_window.clear(_clearColour);
		_window.draw(_canvas.GetSprite());
		_window.display();
	}

private:
	const RenderCanvas& _canvas;
	WindowManager::Window& _window;

	sf::Color _clearColour{ 100, 149, 237 };	// GT_TODO: Make this a constant.
};