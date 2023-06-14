#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\Texture.hpp>

// GT_TODO: I think this should not be a static but instead be instanced. It's a pain to reset state for different views.

class SpriteRenderer
{
public:
	static void SetColour(const sf::Color& colour)
	{
		_sprite.setColor(colour);
	}

	static void SetTexture(const sf::Texture& texture, bool resetRect = false)
	{
		_sprite.setTexture(texture, resetRect);
	}

	static void Draw(sf::RenderTarget& target, const sf::Vector2f& position)
	{
		_sprite.setPosition(position);

		target.draw(_sprite);
	}

	static void Draw(sf::RenderTarget& target, const sf::Vector2f& position, const sf::IntRect& rect, bool flipX = false, bool flipY = false)
	{
		sf::Vector2f originOffset{ rect.width / 2.f, rect.height / 2.f };
		_sprite.setOrigin(originOffset);

		_sprite.setPosition(position + originOffset);
		_sprite.setTextureRect(rect);

		_sprite.setScale(
			sf::Vector2f
			{
				(flipX) ? -1.f : 1.f,
				(flipY) ? -1.f : 1.f
			}
		);

		target.draw(_sprite);
	}

	static void DrawOutline(sf::RenderTarget& target, const sf::Vector2f& position, const sf::IntRect& rect, bool flipX = false, bool flipY = false)
	{
		sf::Color oldColour = _sprite.getColor();
		_sprite.setColor(sf::Color{ 0, 0, 0, oldColour.a });
		Draw(target, position + sf::Vector2f{ 1, 0 }, rect, flipX, flipY);
		Draw(target, position + sf::Vector2f{ -1, 0 }, rect, flipX, flipY);
		Draw(target, position + sf::Vector2f{ 0, 1 }, rect, flipX, flipY);
		Draw(target, position + sf::Vector2f{ 0, -1 }, rect, flipX, flipY);
		_sprite.setColor(oldColour);

		Draw(target, position, rect, flipX, flipY);
	}

private:
	inline static sf::Sprite _sprite;
};