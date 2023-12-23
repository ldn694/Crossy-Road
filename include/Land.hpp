#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

class Land : public Road {
public:
    enum Variant {
        Empty,
        Start,
        Normal,
        NumLandVariants
    };
private:
    const int MAX_NUMBER_OBSTACLE = 6;
    int getNumberObstacles(Variant variant);
public:
    Land(const TextureHolder& textures, Difficulty difficulty, int variant);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

