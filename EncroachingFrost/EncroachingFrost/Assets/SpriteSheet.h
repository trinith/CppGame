#pragma once

#include <Game\Assert.h>
#include <SFML\Graphics\Texture.hpp>

#include <unordered_map>

#pragma optimize("", off)

namespace Assets
{

	class SpriteSheet
	{
	public:
		using SpriteFlags = uint32_t;

	public:
		SpriteSheet(const sf::Texture& texture, sf::Vector2i spriteSize)
			: _texture{ texture }
			, _spriteSize{ spriteSize }
			, _indexMax{ (texture.getSize().x / spriteSize.x) * (texture.getSize().y / spriteSize.y) }	// GT_TODO: Fix this warning! >.<
		{
		}

		SpriteSheet(const SpriteSheet&) = delete;
		SpriteSheet(SpriteSheet&&) = delete;
		SpriteSheet& operator=(const SpriteSheet&) = delete;
		SpriteSheet& operator=(SpriteSheet&&) = delete;

		const sf::Texture& GetTexture() const { return _texture; }
		sf::Vector2i GetSpriteSize() const { return _spriteSize; }
		size_t GetCount() const { return _indexMax; }

		sf::IntRect GetSprite(size_t index) const
		{
			ASSERT(index >= 0 && index < _indexMax);

			const int spritesPerRow = _texture.getSize().x / _spriteSize.x;

			return sf::IntRect
			{
				static_cast<int>((index % spritesPerRow) * _spriteSize.x),
				static_cast<int>((index / spritesPerRow) * _spriteSize.y),
				_spriteSize.x,
				_spriteSize.y
			};
		}

		SpriteFlags GetFlags(size_t index) const
		{
			ASSERT(index >= 0 && index < _indexMax);

			auto findResult = _flags.find(index);

			return (findResult != _flags.end())
				? findResult->second
				: static_cast<SpriteFlags>(0);
		}

		void SetFlags(size_t index, SpriteFlags flags)
		{
			ASSERT(index >= 0 && index < _indexMax);

			_flags[index] = flags;
		}

		bool HasFlag(size_t index, SpriteFlags flagIndex) const
		{
			ASSERT(flagIndex >= 0 && flagIndex << sizeof(SpriteFlags));

			SpriteFlags flagMask = 0x1 << (flagIndex - 1);
			return (GetFlags(index) & flagMask) == flagMask;
		}

	private:
		const sf::Texture& _texture;
		sf::Vector2i _spriteSize;
		std::unordered_map<size_t, SpriteFlags> _flags;

		size_t _indexMax;
	};

}