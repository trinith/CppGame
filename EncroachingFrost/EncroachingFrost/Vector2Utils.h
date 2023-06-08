#pragma once

#include <SFML\System\Vector2.hpp>
#include <ostream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vector)
{
    return os << "{x=" << vector.x << ",y=" << vector.y << "}";
}

template <typename T>
float VectorLength(const sf::Vector2<T>& vector)
{
    return sqrt(VectorLengthSquared(vector));
}

template <typename T>
float VectorLengthSquared(const sf::Vector2<T>& vector)
{
    return vector.x * vector.x + vector.y * vector.y;
}

template <typename T>
sf::Vector2<T> ScaleVector(const sf::Vector2<T>& vector, const sf::Vector2<T>& scale)
{
    return sf::Vector2f{ vector.x * scale.x, vector.y * scale.y };
}