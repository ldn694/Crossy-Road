#include "SRoad.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

SRoad::SRoad(const TextureHolder& textures) : Road(Textures::SRoad, textures, Road::Type::SRoad, Zone::Safety::Unsafe){
}
void SRoad::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
