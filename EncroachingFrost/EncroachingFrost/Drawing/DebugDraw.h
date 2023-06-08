#pragma once

#define DEBUG_DRAW false

#if DEBUG_DRAW

#define DBGD_SPRITERECT true
#define DBGD_TILEOVERLAY true

static class DebugDraw
{
public:
	static const sf::RectangleShape& FilledRectangle(float x, float y, float width, float height, sf::Color colour)
	{
		_rect.setPosition(x, y);
		_rect.setSize(sf::Vector2f{ width, height });
		_rect.setFillColor(colour);
		_rect.setOutlineColor(sf::Color::Transparent);
		_rect.setOutlineThickness(0);

		return _rect;
	}

	static const sf::RectangleShape& FilledRectangle(sf::FloatRect bounds, sf::Color colour)
	{
		return DebugDraw::FilledRectangle(bounds.left, bounds.top, bounds.width, bounds.height, colour);
	}

	static const sf::RectangleShape& Rectangle(float x, float y, float width, float height, sf::Color colour)
	{
		_rect.setPosition(x, y);
		_rect.setSize(sf::Vector2f{ width, height });
		_rect.setFillColor(sf::Color::Transparent);
		_rect.setOutlineColor(colour);
		_rect.setOutlineThickness(-1);

		return _rect;
	}

	static const sf::RectangleShape& Rectangle(sf::FloatRect bounds, sf::Color colour)
	{
		return DebugDraw::Rectangle(bounds.left, bounds.top, bounds.width, bounds.height, colour);
	}

private:
	inline static sf::RectangleShape _rect;
};
#endif