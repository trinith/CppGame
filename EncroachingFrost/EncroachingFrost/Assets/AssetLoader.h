#pragma once

#include <Assets\AssetManager.h>
#include <Game\Assert.h>

#include <Path.h>

#include <string>

namespace Assets
{

	enum class TileFlags : uint32_t
	{
		Blocking = 1,
	};

	struct Textures
	{
		inline static std::string Entities = "Entities";
		inline static std::string Tiles = "Tiles";
	};

	struct SpriteSheetInfo
	{
		std::string AssetName;
		sf::Vector2i SpriteSize;
	};

	struct SpriteSheets
	{
		inline static SpriteSheetInfo Entities{ "Entities", sf::Vector2i{16, 16} };
		inline static SpriteSheetInfo Tiles{ "Tiles", sf::Vector2i{16, 16} };
	};

	struct Fonts
	{
		inline static std::string CombatText = "CombatText";
	};

	class AssetLoader
	{
	public:
		struct Constants
		{
			inline static std::string_view TextureDir = ".\\Content\\Textures";
			inline static std::string_view FontsDir = ".\\Content\\Fonts";
		};

	public:
		static void LoadTextures(AssetManager& assetManager)
		{
			AssetManager::Textures& textures = assetManager.GetTextures();
			CreateAndLoadTexture(textures, Textures::Entities, Path::Combine(Constants::TextureDir, "SpriteSheet_Entities.png"));
			CreateAndLoadTexture(textures, Textures::Tiles, Path::Combine(Constants::TextureDir, "SpriteSheet_Tiles.png"));
		}

		static void LoadSpriteSheets(AssetManager& assetManager)
		{
			const AssetManager::Textures& textures = assetManager.GetTextures();
			AssetManager::SpriteSheets& spriteSheets = assetManager.GetSpriteSheets();

			CreateSpriteSheet(spriteSheets, SpriteSheets::Entities, textures, Textures::Entities);

			SpriteSheet& tiles = CreateSpriteSheet(spriteSheets, SpriteSheets::Tiles, textures, Textures::Tiles);
			tiles.SetFlags(30, static_cast<uint32_t>(TileFlags::Blocking));
			tiles.SetFlags(32, static_cast<uint32_t>(TileFlags::Blocking));
			tiles.SetFlags(48, static_cast<uint32_t>(TileFlags::Blocking));
		}

		static void LoadFonts(AssetManager& assetManager)
		{
			AssetManager::Fonts& fonts = assetManager.GetFonts();
			CreateAndLoadFont(fonts, Fonts::CombatText, Path::Combine(Constants::FontsDir, "arial.ttf"));
		}

	private:
		static void CreateAndLoadTexture(AssetManager::Textures& textures, const std::string& assetName, const std::string& fileName)
		{
			auto texture = textures.Create(assetName);
			ASSERT(texture);
			ASSERT(texture->get().loadFromFile(fileName));
		}

		static SpriteSheet& CreateSpriteSheet(AssetManager::SpriteSheets& spriteSheets, const SpriteSheetInfo& spriteSheetInfo, const AssetManager::Textures& textures, const std::string& textureName)
		{
			auto texture = textures[textureName];
			ASSERT(texture);

			const sf::Texture& actualTexture = texture->get();
			auto spriteSheet = spriteSheets.Create(spriteSheetInfo.AssetName, texture->get(), spriteSheetInfo.SpriteSize);
			ASSERT(spriteSheet);

			return *spriteSheet;
		}

		static void CreateAndLoadFont(AssetManager::Fonts& fonts, const std::string& assetName, const std::string& fileName)
		{
			auto font = fonts.Create(assetName);
			ASSERT(font);
			ASSERT(font->get().loadFromFile(fileName));
		}
	};

}