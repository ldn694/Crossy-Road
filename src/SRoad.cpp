#include "SRoad.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

SRoad::SRoad(const TextureHolder& textures, Difficulty difficulty, int variant) : Road(Textures::SRoad, textures, Road::Type::SRoad, Zone::Safety::Safe, difficulty){
}
void SRoad::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
