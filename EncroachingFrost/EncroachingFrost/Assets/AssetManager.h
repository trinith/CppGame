#pragma once

#include <Assets\AssetBank.h>
#include <Assets\SpriteSheet.h>

#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Texture.hpp>

namespace Assets
{

	class AssetManager
	{
	public:
		using Textures = AssetBank<sf::Texture>;
		using SpriteSheets = AssetBank<SpriteSheet>;
		using Fonts = AssetBank<sf::Font>;

	public:
		Textures& GetTextures() { return _textures; }
		const Textures& GetTextures() const { return _textures; }

		SpriteSheets& GetSpriteSheets() { return _spriteSheets; }
		const SpriteSheets& GetSpriteSheets() const { return _spriteSheets; }

		Fonts& GetFonts() { return _fonts; }
		const Fonts& GetFonts() const { return _fonts; }

	private:
		Textures _textures;
		SpriteSheets _spriteSheets;
		Fonts _fonts;
	};

}