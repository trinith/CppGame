#pragma once

#include <WindowManager.h>
#include <Game\Assert.h>
#include <SFML\Graphics.hpp>

class RenderCanvas
{
public:
	RenderCanvas(const WindowManager& windowManager, sf::Vector2i canvasSize, sf::Vector2f canvasScale)
		: _worldSize{ canvasSize }
		, _canvasScale{ canvasScale }
	{
		ASSERT(_canvas.create(_worldSize.x, _worldSize.y));
		_sprite.setTexture(_canvas.getTexture());
		_sprite.setScale(_canvasScale);

		_screenSize = static_cast<sf::Vector2i>(windowManager.GetWindow().getSize());
		_sprite.setPosition(
			sf::Vector2f
			{
				_screenSize.x / 2.f - _worldSize.x * _canvasScale.x / 2.f,
				_screenSize.y / 2.f - _worldSize.y * _canvasScale.y / 2.f
			}
		);

		_canvas.setSmooth(false);
	}

	sf::RenderTexture& GetTarget() { return _canvas; }
	const sf::Sprite& GetSprite() const { return _sprite; }

	const sf::Vector2i GetWorldSize() const { return _worldSize; }

	sf::Vector2i ScreenToWorld(const sf::Vector2i p) const
	{
		const sf::Vector2i canvasPos = static_cast<sf::Vector2i>(_sprite.getPosition());

		const sf::Vector2i worldPos
		{
			static_cast<int>((p.x - canvasPos.x) / _canvasScale.x),
			static_cast<int>((p.y - canvasPos.y) / _canvasScale.y)
		};

		return worldPos;
	}

private:
	sf::Vector2i _screenSize;
	sf::Vector2i _worldSize;
	sf::Vector2f _canvasScale;

	sf::RenderTexture _canvas;
	sf::Sprite _sprite;
};