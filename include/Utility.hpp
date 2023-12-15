#pragma once

#include <string>
#include "SFML/System/Time.hpp"


namespace sf
{
	class Sprite;
	class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

void assertThrow(bool expression, std::string message);

#include "Utility.inl"
