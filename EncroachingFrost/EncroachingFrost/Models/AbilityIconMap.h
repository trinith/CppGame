#pragma once

#include <Game\Assert.h>
#include <Models\EntityAbilities.h>

#include <unordered_map>
#include <optional>

class AbilityIconMap
{
public:
	static std::optional<size_t> GetIcon(AbilityId id)
	{
		ASSERT(_isInitialized);
		const auto findResult = _iconMap.find(id);

		if (findResult == _iconMap.end())
			return std::nullopt;

		return findResult->second;
	}

	static bool HasIcon(AbilityId id)
	{
		ASSERT(_isInitialized);
		const auto findResult = _iconMap.find(id);
		return findResult != _iconMap.end();
	}

	static void Initialize()
	{
		_isInitialized = true;

		_iconMap.emplace(AbilityId::Fireball, 30);
		_iconMap.emplace(AbilityId::FireBlast, 31);
	}

private:
	inline static bool _isInitialized;
	inline static std::unordered_map<AbilityId, size_t> _iconMap;
};