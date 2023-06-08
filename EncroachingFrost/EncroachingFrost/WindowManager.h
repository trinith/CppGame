#pragma once

#include <Game\IController.h>
#include <SFML\Graphics.hpp>

class WindowManager : public GhettoEngine::IController
{
public:
	using Window = sf::RenderWindow;

	WindowManager(Window& window)
		: _window{ window }
	{
	}

	const Window& GetWindow() const { return _window; }
	Window& GetWindow() { return _window; }

	void Close() const { _window.close(); }

	bool IsOpen() const { return _window.isOpen(); }

	virtual void FixedUpdate(const GhettoEngine::GameTime& gameTime) override {}

	virtual void Update(const GhettoEngine::GameTime& gameTime) override
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					_window.close();
					break;
				case sf::Event::GainedFocus:
					_hasFocus = true;
					break;
				case sf::Event::LostFocus:
					_hasFocus = false;
					break;
			}
		}
	}

	bool HasFocus() const { return _hasFocus; }

private:
	Window& _window;
	bool _hasFocus = true;
};