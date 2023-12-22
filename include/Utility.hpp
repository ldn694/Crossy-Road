#pragma once

#include <string>
#include <stdlib.h>
#include <time.h> 
#include "SFML/System/Time.hpp"
#include <SFML/Graphics/Rect.hpp>


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
void setSize(sf::Sprite& sprite, float width, float height);
void setSize(sf::Sprite& sprite, sf::Vector2f size);


float intersection(sf::FloatRect rect1, sf::FloatRect rect2);
float squaredDistance(sf::Vector2f v1, sf::Vector2f v2);

void assertThrow(bool expression, std::string message);

int Rand(int l, int r);

#include "Utility.inl"
