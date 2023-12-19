#include "Land.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Land::Land(const TextureHolder& textures) : Road(Textures::Land, textures, Road::Type::Land, Zone::Safety::Safe){
}
void Land::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
