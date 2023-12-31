#include "Utility.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>


void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void setSize(sf::Sprite& sprite, float width, float height)
{
	sf::Vector2u textureSize = sprite.getTexture()->getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setScale(width / bounds.width, height / bounds.height);
}

void setSize(sf::Sprite& sprite, sf::Vector2f size)
{
	setSize(sprite, size.x, size.y);
}

float intersection(sf::FloatRect rect1, sf::FloatRect rect2) {
	float x1 = rect1.left;
	float y1 = rect1.top;
	float x2 = rect1.left + rect1.width;
	float y2 = rect1.top + rect1.height;

	float x3 = rect2.left;
	float y3 = rect2.top;
	float x4 = rect2.left + rect2.width;
	float y4 = rect2.top + rect2.height;

	float x5 = std::max(x1, x3);
	float y5 = std::max(y1, y3);
	float x6 = std::min(x2, x4);
	float y6 = std::min(y2, y4);

	if (x5 > x6 || y5 > y6) {
		return 0;
	}
	return (x6 - x5) * (y6 - y5);
}

float squaredDistance(sf::Vector2f v1, sf::Vector2f v2) {
	return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y);
}

void assertThrow(bool expression, std::string message) {
	if (!expression) {
		std::cout << "ERROR: " << message << "\n";
		assert(false);
	}
}

int Rand(int l, int r) {
	return rand() % (r - l + 1) + l;
}

std::vector <int> randomIntSampling(int n, int k) {
    assert(0 <= k && k <= n);
    std::vector <int> s;
    for (int i = 0; i < n; i++) {
        s.push_back(i);
    }
    std::vector <int> res = randomSampling<int>(s, k);
    sort(res.begin(), res.end());
    return res;
}