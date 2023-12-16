#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

class River : public Road{
private:
public:
    River(const TextureHolder& textures);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
};

