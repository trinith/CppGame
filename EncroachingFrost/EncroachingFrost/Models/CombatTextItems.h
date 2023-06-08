#pragma once

#include <Entities\IGameEntity.h>
#include <Game\Assert.h>
#include <Models\EntityBounds.h>
#include <SFML\System\Vector2.hpp>

#include <string>
#include <vector>

struct CombatTextItem
{
	CombatTextItem(const std::string& text, const IGameEntity& target, AbilityType type)
		: Text{ text }
		, Target{ target }
		, Type{ type }
		, Offset{ 0, 0 }
	{
		sf::FloatRect spriteRect{ target.GetBounds().Position, target.GetBounds().Size };
		target.GetHitboxes().ApplySpriteHitbox(spriteRect);
		Offset.x += spriteRect.width / 2.f;
		Offset.y += spriteRect.height / 2.f;
	}

	std::string Text;
	std::reference_wrapper<const IGameEntity> Target;
	AbilityType Type;

	sf::Vector2f Offset{ 0, 0 };
	sf::Vector2f Dir{ 0, -1 };
	float Speed = 15;
	float TimeRemaining = 2.f;
};

// GT_TODO: Consider make this an object. We'll want to update this vector when we get around to entities dying.
using CombatTextItems = std::vector<CombatTextItem>;
