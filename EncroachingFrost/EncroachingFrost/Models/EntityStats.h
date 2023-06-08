#pragma once

#include <optional>
#include <string>

struct EntityStats
{
	EntityStats(const std::string& name, float maxHealth, std::optional<float> maxPower = std::nullopt, float baseStrength = 1.f)
		: Name{ name }
		, MaxHealth{ maxHealth }
		, Health{ maxHealth }
		, MaxPower{ maxPower }
		, Power{ maxPower }
		, BaseStrength{ baseStrength }
	{
	}

	std::string Name;

	float MaxHealth;
	float Health;

	bool CanLoseHealth = true;
	bool CanBeDamaged = true;

	std::optional<float> MaxPower;
	std::optional<float> Power;

	float BaseStrength;

	void ModifyHealth(float amount)
	{
		Health = std::clamp<float>(Health + amount, 0, MaxHealth);
	}

	void ModifyPower(float amount)
	{
		if (Power)
			Power = std::clamp<float>(*Power + amount, 0, *MaxPower);
	}
};