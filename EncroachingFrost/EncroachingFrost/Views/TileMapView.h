#pragma once

#include <Assets\SpriteSheet.h>
#include <Drawing\DebugDraw.h>
#include <Game\ViewBase.h>
#include <Models\TileMap.h>

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\Sprite.hpp>

class TileMapView : public GhettoEngine::ViewBase
{
public:
	TileMapView(sf::RenderTarget& renderTarget, const TileMap& tiles, const Assets::SpriteSheet& spriteSheet)
		: _renderTarget{ renderTarget }
		, _tiles{ tiles }
		, _spriteSheet{ spriteSheet }
	{
	}

protected:
	virtual void OnDraw(const GhettoEngine::GameTime&) override
	{
		sf::Vector2i spriteSize = _spriteSheet.GetSpriteSize();
		SpriteRenderer::SetColour(sf::Color{ 255, 255, 255, 255 });
		SpriteRenderer::SetTexture(_spriteSheet.GetTexture());

		for (size_t x = 0; x < _tiles.GetWidth(); ++x)
		{
			for (size_t y = 0; y < _tiles.GetHeight(); ++y)
			{
				size_t tileIndex = _tiles.Get(x, y);
				sf::Vector2f pos{
					static_cast<float>(x * spriteSize.x),
					static_cast<float>(y * spriteSize.y)
				};

				SpriteRenderer::Draw(_renderTarget, pos, _spriteSheet.GetSprite(tileIndex));

#if DBGD_TILEOVERLAY
				if (_spriteSheet.HasFlag(tileIndex, static_cast<Assets::SpriteSheet::SpriteFlags>(Assets::TileFlags::Blocking)))
				{
					_renderTarget.draw(DebugDraw::FilledRectangle(pos.x, pos.y, spriteSize.x, spriteSize.y, sf::Color{ 255, 0, 0, 32 }));
				}
#endif
			}
		}
	}

private:
	sf::RenderTarget& _renderTarget;
	const TileMap& _tiles;
	const Assets::SpriteSheet& _spriteSheet;
};