#pragma once

#include <Assets\SpriteSheet.h>
#include <Drawing\DebugDraw.h>
#include <Drawing\SpriteRenderer.h>
#include <Entities\IGameEntity.h>
#include <Game\ViewBase.h>
#include <Models\EntityReferenceList.h>
#include <SFML\Graphics.hpp>

#include <map>

class EntityView : public GhettoEngine::ViewBase
{
public:
	EntityView(sf::RenderTarget& target, const EntityReferenceList<IGameEntity>& entities, const Assets::SpriteSheet& spriteSheet)
		: _target{ target }
		, _entities{ entities }
		, _spriteSheet{ spriteSheet }
	{
	}

protected:
	virtual void OnDraw(const GhettoEngine::GameTime& gameTime) override
	{
		// Order the entities so that ones near the top of the screen are drawn first.
		std::map<int, EntityReferenceList<IGameEntity>> orderedEntities;
		for (auto&& entityRef : _entities)
		{
			const EntityBounds& bounds = entityRef.get().GetBounds();
			orderedEntities[bounds.Position.y + bounds.Size.y].emplace_back(entityRef);
		}

		for (auto&& [_, entityList] : orderedEntities)
		{
			for (auto&& entityRef : entityList)
			{
				const IGameEntity& entity = entityRef.get();
				const EntitySprites& sprites = entity.GetSprites();
				if (!sprites.Main)
					continue;

				const EntityBounds& bounds = entity.GetBounds();
				const EntityHitboxes& hitboxes = entity.GetHitboxes();

				// Align with pixel grid
				sf::Vector2f pos = static_cast<sf::Vector2f>(static_cast<sf::Vector2i>(bounds.Position)); // +offset;
				hitboxes.ApplySpriteHitbox(pos);

				// Draw the sprite
				SpriteRenderer::SetColour(sf::Color{ 255, 255, 255, sprites.MainAlpha });
				SpriteRenderer::SetTexture(_spriteSheet.GetTexture());
				SpriteRenderer::DrawOutline(_target, pos, _spriteSheet.GetSprite(*sprites.Main));

#if DBGD_SPRITERECT
				{
					sf::FloatRect rect{ bounds.Position, bounds.Size };
					hitboxes.ApplySpriteHitbox(rect);
					_target.draw(DebugDraw::Rectangle(rect, sf::Color{ 255, 192, 203, 128 }));
				}

				if (hitboxes.Ground)
				{
					sf::FloatRect rect{ bounds.Position, bounds.Size };
					hitboxes.ApplyGroundHitbox(rect);
					_target.draw(DebugDraw::Rectangle(rect, sf::Color{ 255, 0, 0, 128 }));
				}

				if (hitboxes.Selection)
				{
					sf::FloatRect rect{ bounds.Position, bounds.Size };
					hitboxes.ApplySelectionHitbox(rect);
					_target.draw(DebugDraw::Rectangle(rect, sf::Color{ 0, 255, 0, 128 }));
				}
#endif
			}
		}
	}

private:
	sf::RenderTarget& _target;
	const EntityReferenceList<IGameEntity>& _entities;
	const Assets::SpriteSheet& _spriteSheet;
};