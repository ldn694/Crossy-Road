#pragma once

#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include "SFML/System/Time.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>


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

std::string             keyCodeToString(sf::Keyboard::Key keyCode);
sf::Keyboard::Key       stringToSFMLKey(const std::string& keyString);

float intersection(sf::FloatRect rect1, sf::FloatRect rect2);
float squaredDistance(sf::Vector2f v1, sf::Vector2f v2);

void assertThrow(bool expression, std::string message);

int Rand(int l, int r);

template <typename T>
std::vector <T> randomSampling(std::vector <T> s, int k) {
    if (k == 0) {
        return std::vector <T>();
    }
    int n = s.size();
    assertThrow(1 <= k && k <= n, "k must be in [1, n]");
    std::vector <T> res(k);
    for (int i = 0; i < k; i++) {
        res[i] = s[i];
    }
    for (int i = k; i < n; i++) {
        int j = Rand(0, i);
        if (j < k) {
            res[j] = s[i];
        }
    }
    return res;
}

std::vector <int> randomIntSampling(int n, int k);

#include "Utility.inl"
