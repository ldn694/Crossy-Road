#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

class Railways : public Road{
public:
    enum Variant {
        Left,
        Right
    };
private:
    Variant mVariant;
public:
    Railways(const TextureHolder& textures, Difficulty difficulty, int variant);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

