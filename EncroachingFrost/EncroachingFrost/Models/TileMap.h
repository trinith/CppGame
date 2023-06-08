#pragma once

#include <Game\Assert.h>

#include <memory>

class TileMap
{
public:
	TileMap(size_t width, size_t height)
		: _tiles{ std::make_unique<size_t[]>(width * height) }
		, _numTiles{ width * height }
		, _width{ width }
		, _height{ height }
	{
	}

	TileMap(const TileMap&) = delete;
	TileMap(TileMap&&) = delete;
	TileMap& operator=(const TileMap&) = delete;
	TileMap& operator=(TileMap&&) = delete;

	size_t GetWidth() const { return _width; }
	size_t GetHeight() const { return _height; }
	size_t GetNumTiles() const { return _numTiles; }

	void Set(size_t x, size_t y, size_t tileIndex)
	{
		const size_t index = GetIndex(x, y);
		ASSERT(index >= 0 && index < _numTiles);
		_tiles[index] = tileIndex;
	}

	void Set(std::initializer_list<size_t> tileData, size_t xOffset = 0, size_t yOffset = 0)
	{
		size_t offsetIndex = GetIndex(xOffset, yOffset);
		const size_t dataSize = tileData.size() - 1 ;
		ASSERT(offsetIndex >= 0 && offsetIndex + dataSize < _numTiles);

		for (size_t tile : tileData)
			_tiles[offsetIndex++] = tile;
	}

	size_t Get(size_t x, size_t y) const
	{
		return Get(GetIndex(x, y));
	}

	size_t Get(size_t index) const
	{
		ASSERT(index >= 0 && index < _numTiles);
		return _tiles[index];
	}

private:
	size_t GetIndex(size_t x, size_t y) const { return _width * y + x; }

	std::unique_ptr<size_t[]> _tiles;
	size_t _numTiles;
	size_t _width;
	size_t _height;
};