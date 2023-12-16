#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

class Land : public Road{
private:
public:
    Land(const TextureHolder& textures);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
};

