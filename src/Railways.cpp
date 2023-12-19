#include "Railways.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Railways::Railways(const TextureHolder& textures) : Road(Textures::Railways, textures, Road::Type::Railways, Zone::Safety::Safe){
}
void Railways::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
