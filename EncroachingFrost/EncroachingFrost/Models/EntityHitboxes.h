#pragma once

#include <SFML\Graphics\Rect.hpp>

#include <optional>

struct EntityHitboxes
{
	std::optional<sf::FloatRect> Ground;
	std::optional<sf::FloatRect> Sprite;
	std::optional<sf::FloatRect> Selection;

	void ApplyGroundHitbox(sf::FloatRect& baseRect) const
	{
		if (Ground)
		{
			baseRect.left += Ground->left;
			baseRect.top += Ground->top;
			baseRect.width = Ground->width;
			baseRect.height = Ground->height;
		}
	}

	void ApplyGroundHitbox(sf::Vector2f& basePoint) const
	{
		if (Ground)
		{
			basePoint.x += Ground->left;
			basePoint.y += Ground->top;
		}
	}

	void ApplySpriteHitbox(sf::FloatRect& baseRect) const
	{
		if (Sprite)
		{
			baseRect.left += Sprite->left;
			baseRect.top += Sprite->top;
			baseRect.width = Sprite->width;
			baseRect.height = Sprite->height;
		}
	}

	void ApplySpriteHitbox(sf::Vector2f& basePoint) const
	{
		if (Sprite)
		{
			basePoint.x += Sprite->left;
			basePoint.y += Sprite->top;
		}
	}

	void ApplySelectionHitbox(sf::FloatRect& baseRect) const
	{
		ApplySpriteHitbox(baseRect);

		if (Selection)
		{
			baseRect.left += Selection->left;
			baseRect.top += Selection->top;
			baseRect.width = Selection->width;
			baseRect.height = Selection->height;
		}
	}

	void ApplySelectionHitbox(sf::Vector2f& basePoint) const
	{
		ApplySpriteHitbox(basePoint);

		if (Selection)
		{
			basePoint.x += Selection->left;
			basePoint.y += Selection->top;
		}
	}
};