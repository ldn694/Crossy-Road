#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

class Land : public Road{
private:
    const int MAX_NUMBER_ROCKS = 2;
public:
    Land(const TextureHolder& textures, Difficulty difficulty);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

