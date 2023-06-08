#pragma once

#include <SFML\System\Vector2.hpp>

#include <optional>

struct PlayerUseInputModel
{
	std::optional<sf::Vector2i> worldPosition;
};