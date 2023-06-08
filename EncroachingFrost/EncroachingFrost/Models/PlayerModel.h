#pragma once

#include <Game\OptionalRef.h>

#include <Models\EntityAbilities.h>
#include <Models\EntityAbilityCooldowns.h>
#include <Models\EntityAbilityQueue.h>
#include <Models\EntityBounds.h>
#include <Models\EntityHitboxes.h>
#include <Models\EntityStats.h>
#include <Models\EntitySprites.h>

#include <SFML\System\Vector2.hpp>

struct PlayerModel
{
	EntityBounds Bounds{ {9.5f * 16, 12.5f * 16}, {16, 16} };
	EntityStats Stats{ "Player", Constants::MaxHealth, Constants::MaxPower, Constants::BaseStrength };
	EntitySprites Sprites{ Constants::Sprites::Main, Constants::Sprites::Shadow };

	EntityAbilities Abilities
	{
		AbilityId::Empty,
		AbilityId::Fireball,
		AbilityId::FireBlast,
		AbilityId::Empty,
		AbilityId::Empty
	};

	EntityHitboxes Hitboxes
	{
		sf::FloatRect{2, 10, 12, 6 },
		sf::FloatRect{0, -3, 16, 16},
		std::nullopt
	};

	sf::Vector2f NextPosition{ 0, 0 };

	sf::Vector2f Dir{ 0, 0 };
	float Speed = Constants::MaxSpeed;

	OptionalRef<IGameEntity> Target;
	EntityAbilityQueue AbilityQueue;
	EntityAbilityCooldowns AbilityCooldowns;

	struct Constants
	{
		inline static const float MaxHealth = 100;
		inline static const float MaxPower = 100;
		inline static const float BaseStrength = 10;

		inline static const float MaxSpeed = 60;
		inline static const float PassivePowerDrain = 1; // Per second
		inline static const float ColdHealthDrain = 1; // Per second

		struct Sprites
		{
			inline static const size_t Main = 0;
			inline static const size_t Shadow = 15;
		};
	};
};