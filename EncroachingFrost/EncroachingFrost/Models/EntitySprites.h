#pragma once

#include <optional>

struct EntitySprites
{
	std::optional<size_t> Main;
	std::optional<size_t> Shadow;

	sf::Uint8 MainAlpha = 255;
	sf::Uint8 ShadowAlpha = 128;
};