#pragma once

#include <Assets\SpriteSheet.h>
#include <Drawing\SpriteRenderer.h>
#include <Entities\IGameEntity.h>
#include <Game\ViewBase.h>
#include <Models\EntityReferenceList.h>
#include <SFML\Graphics.hpp>

class EntityShadowView : public GhettoEngine::ViewBase
{
public:
	EntityShadowView(sf::RenderTarget& target, const EntityReferenceList<IGameEntity>& entities, const Assets::SpriteSheet& spriteSheet)
		: _target{ target }
		, _entities{ entities }
		, _spriteSheet{ spriteSheet }
	{
	}

protected:
	virtual void OnDraw(const GhettoEngine::GameTime& gameTime) override
	{
		for (auto&& entityRef : _entities)
		{
			const IGameEntity& entity = entityRef.get();
			const EntitySprites& sprites = entity.GetSprites();
			const EntityBounds& bounds = entity.GetBounds();

			if (!sprites.Shadow)
				continue;

			sf::Vector2f pos = static_cast<sf::Vector2f>(static_cast<sf::Vector2i>(bounds.Position));

			// Draw the sprite
			SpriteRenderer::SetColour(sf::Color{ 255, 255, 255, sprites.ShadowAlpha });
			SpriteRenderer::SetTexture(_spriteSheet.GetTexture());
			SpriteRenderer::Draw(_target, pos, _spriteSheet.GetSprite(*sprites.Shadow));
		}
	}

private:
	sf::RenderTarget& _target;
	const EntityReferenceList<IGameEntity>& _entities;
	const Assets::SpriteSheet& _spriteSheet;
};