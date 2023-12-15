#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

class Railways : public Road{
private:
public:
    Railways(const TextureHolder& textures);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
};

