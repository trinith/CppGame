#pragma once

#include <Assets\SpriteSheet.h>
#include <Game\ControllerBase.h>
#include <Models\PlayerModel.h>
#include <Models\TileMap.h>

class PlayerMoveController : public GhettoEngine::ControllerBase
{
public:
	PlayerMoveController(PlayerModel& model, const TileMap& tileMap, const Assets::SpriteSheet& spriteSheet)
		: _model{ model }
		, _tileMap{ tileMap }
		, _spriteSheet{ spriteSheet }
	{
	}

protected:
	virtual void OnFixedUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		_model.NextPosition = _model.Bounds.Position;

		if (_model.Dir.x != 0 or _model.Dir.y != 0)
		{
			const sf::Vector2f moveIncrement = _model.Dir * gameTime.ElapsedSeconds.count() * _model.Speed;
	
			if (_model.Hitboxes.Ground)
			{
				const sf::FloatRect& hitbox = *_model.Hitboxes.Ground;
				_model.NextPosition.x = MovePointX(_model.Bounds.Position, moveIncrement.x, hitbox);
				_model.NextPosition.y = MovePointY(_model.Bounds.Position, moveIncrement.y, hitbox);
			}
			else
			{
				_model.NextPosition += moveIncrement;
			}
		}
	}

private:
	bool IsPointBlocked(const sf::Vector2f& p)
	{
		const sf::Vector2i spriteSize = _spriteSheet.GetSpriteSize();
		size_t tile = _tileMap.Get(
			static_cast<size_t>(p.x / spriteSize.x),
			static_cast<size_t>(p.y / spriteSize.y)
		);
		return _spriteSheet.HasFlag(tile, static_cast<Assets::SpriteSheet::SpriteFlags>(Assets::TileFlags::Blocking));
	}

	float MovePointX(const sf::Vector2f& position, float xInc, const sf::FloatRect& hitbox)
	{
		const float newX = position.x + xInc;
		const float outsideEdgeX = (xInc > 0) ? hitbox.left + hitbox.width - 1 : hitbox.left;

		const sf::Vector2f top
		{
			newX + outsideEdgeX,
			position.y + hitbox.top
		};

		const sf::Vector2f bottom
		{
			newX + outsideEdgeX,
			position.y + hitbox.top + hitbox.height - 1
		};

		const bool blocked = IsPointBlocked(top) or IsPointBlocked(bottom);
		if (!blocked)
			return newX;

		return position.x;
	}

	float MovePointY(const sf::Vector2f& position, float yInc, const sf::FloatRect& hitbox)
	{
		const float newY = position.y + yInc;
		const float outsideEdgeY = (yInc > 0) ? hitbox.top + hitbox.height - 1 : hitbox.top;

		const sf::Vector2f left
		{
			position.x + hitbox.left,
			newY + outsideEdgeY
		};

		const sf::Vector2f right
		{
			position.x + hitbox.left + hitbox.width - 1,
			newY + outsideEdgeY
		};

		const bool blocked = IsPointBlocked(left) or IsPointBlocked(right);
		if (!blocked)
			return newY;

		return position.y;
	}

	PlayerModel& _model;
	const TileMap& _tileMap;
	const Assets::SpriteSheet& _spriteSheet;
};