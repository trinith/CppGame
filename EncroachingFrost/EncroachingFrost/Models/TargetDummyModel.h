#pragma once

#include <Models\EntityBounds.h>
#include <Models\EntitySprites.h>
#include <Models\EntityStats.h>

struct TargetDummyModel
{
	TargetDummyModel(const sf::Vector2f& position)
		: Bounds{ position, {16, 16} }
	{
		Stats.CanLoseHealth = false;
	}

	EntityBounds Bounds;
	EntitySprites Sprites{ Constants::Sprites::Main, Constants::Sprites::Shadow };
	EntityStats Stats{ "Target Dummy", 100 };

	EntityHitboxes Hitboxes
	{
		sf::FloatRect{2, 10, 12, 6 },
		sf::FloatRect{0, -3, 16, 16},
		std::nullopt
	};

	struct Constants
	{
		struct Sprites
		{
			inline static const size_t Main = 32;
			inline static const size_t Shadow = 15;
		};
	};
};