#pragma once

#include <Models\EntityAbilities.h>

class GlobalAbilityRegistry
{
public:
	static const AbilityRegistry Registry;

private:
	struct RegistryImpl : public AbilityRegistry
	{
		RegistryImpl()
		{
			//										Name			Mult	Help/Harm			Cost	Cast Time		Cooldown		Range
			RegisterAbility(AbilityId::Ignite,		"Ignite",		1.f,	AbilityType::Harm,	10.f,	std::nullopt,	std::nullopt,	192.f); // GT_TODO: Needs to support periodic effects.
			RegisterAbility(AbilityId::Fireball,	"Fireball",		1.f,	AbilityType::Harm,	10.f,	2.f,			std::nullopt,	192.f);
			RegisterAbility(AbilityId::FireBlast,	"Fire Blast",	2.f,	AbilityType::Harm,	30.f,	std::nullopt,	3.f,			128.f);	// GT_TODO: Bump this up to 30s after testing.
			RegisterAbility(AbilityId::FlameShield, "Flame Shield",	1.f,	AbilityType::Help,	30.f,	std::nullopt,	30.f,			0.f);
			RegisterAbility(AbilityId::Cauterize,	"Cauterize",	1.f,	AbilityType::Help,	30.f,	2.f,			30.f,			0.f);
		}
	};
};

const AbilityRegistry GlobalAbilityRegistry::Registry = GlobalAbilityRegistry::RegistryImpl{};
