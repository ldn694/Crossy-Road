#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

class Land : public Road{
public:
    enum Variant{
        Empty,
        Normal,
        NumLandVariants
    };
private:
    const int MAX_NUMBER_ROCKS = 2;
    int getNumberRocks(Variant variant);
public:
    Land(const TextureHolder& textures, Difficulty difficulty, int variant);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

