#pragma once

#include <Vector2Utils.h>
#include <Entities\IGameEntity.h>
#include <SFML\Graphics\Rect.hpp>

namespace EntityUtils
{

	float DistanceBetweenSpriteCentres(const IGameEntity& lhs, const IGameEntity& rhs)
	{
		sf::FloatRect lhsRect{ lhs.GetBounds().Position, lhs.GetBounds().Size };
		lhs.GetHitboxes().ApplySpriteHitbox(lhsRect);
		sf::Vector2f lhsCentre{ lhsRect.left + lhsRect.width / 2.f, lhsRect.top + lhsRect.height / 2.f };

		sf::FloatRect rhsRect{ rhs.GetBounds().Position, rhs.GetBounds().Size };
		rhs.GetHitboxes().ApplySpriteHitbox(rhsRect);
		sf::Vector2f rhsCentre{ rhsRect.left + rhsRect.width / 2.f, rhsRect.top + rhsRect.height / 2.f };

		return VectorLength(rhsCentre - lhsCentre);
	}

}