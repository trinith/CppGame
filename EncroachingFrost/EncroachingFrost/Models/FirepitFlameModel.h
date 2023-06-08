#pragma once

#include <Models\EntityBounds.h>
#include <Models\EntitySprites.h>
#include <Models\EntityStats.h>
#include <Models\EntityHitboxes.h>
#include <Models\EntityAnimation.h>

struct FirepitFlameModel
{
	FirepitFlameModel(const sf::Vector2f& position)
		: Bounds{ position, {16, 16} }
	{
		Stats.CanLoseHealth = false;
	}

	EntityBounds Bounds;
	EntitySprites Sprites{ Constants::Sprites::FlamesHigh[0], std::nullopt };
	EntityStats Stats{ "Fire Pit", 1, Constants::MaxPower, 0.f };
	EntityHitboxes Hitboxes{ std::nullopt, std::nullopt, std::nullopt };
	EntityAnimation Animation{ Constants::Sprites::FlamesHigh };

	struct Constants
	{
		inline static const float MaxPower = 100.f;
		inline static const float PowerDrain = 10; // Per second
		inline static const float ChargeDistance = 22.627;

		struct Sprites
		{
			inline static const std::vector<size_t> FlamesHigh{ 64, 65, 66 };
		};
	};
};