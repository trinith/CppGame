#pragma once

#include <optional>
#include <string>
#include <vector>

enum class AbilityId
{
	Empty,
	Ignite,
	Fireball,
	FireBlast,
	FlameShield,
	Cauterize,
};

enum class AbilityType
{
	Help,
	Harm,
};

struct EntityAbility
{
	struct Constants
	{
		inline static const float DefaultStrengthMultiplier = 1.f;
		inline static const AbilityType DefaultAbilityType = AbilityType::Harm;
		inline static const float DefaultRange = 192.f;
	};

	EntityAbility(
		const std::string& name,
		float strengthMultiplier = Constants::DefaultStrengthMultiplier,
		AbilityType type = Constants::DefaultAbilityType,
		std::optional<float> cost = std::nullopt,
		std::optional<float> castTime = std::nullopt,
		std::optional<float> cooldown = std::nullopt,
		float range = Constants::DefaultRange
	) 
		: Name{ name }
		, StrengthMultiplier{ strengthMultiplier }
		, Type{ type }
		, Cost{ cost }
		, CastTime{ castTime }
		, Cooldown{ cooldown }
		, Range{ range }
	{
	}

	std::string Name;
	float StrengthMultiplier = 1.f;

	AbilityType Type{ AbilityType::Harm };

	std::optional<float> Cost;
	std::optional<float> CastTime;
	std::optional<float> Cooldown;

	float Range;
};

class AbilityRegistry
{
public:
	const OptionalRef<const EntityAbility> GetAbility(AbilityId name) const
	{
		if (name == AbilityId::Empty)
			return std::nullopt;

		auto findResult = _registry.find(name);
		if (findResult != _registry.end())
			return findResult->second;

		return std::nullopt;
	}

protected:
	template<typename... TArgs>
	void RegisterAbility(AbilityId name, TArgs&&... args)
	{
		auto findResult = _registry.find(name);
		ASSERT(findResult == _registry.end());

		_registry.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(std::forward<TArgs>(args)...)
		);
	}

	std::unordered_map<AbilityId, const EntityAbility> _registry;
};

using EntityAbilities = std::vector<AbilityId>;