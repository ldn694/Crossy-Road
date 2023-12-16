#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

class SRoad : public Road{
private:
public:
    SRoad(const TextureHolder& textures);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
};

