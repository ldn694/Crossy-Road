#include "Railways.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Railways::Railways(const TextureHolder& textures, Difficulty difficulty) : Road(Textures::Railways, textures, Road::Type::Railways, Zone::Safety::Safe, difficulty){
}
void Railways::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
