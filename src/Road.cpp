#include "Road.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
Road::Road(Textures::ID ID, const TextureHolder& textures, Road::Type type): mSprite(textures.get(ID)), Entity(textures.get(ID).getSize())
{
    mSprite.setTexture(textures.get(ID));
    mSprite.setScale(WITDH_SIZE / mSprite.getGlobalBounds().width, HEIGHT_SIZE / mSprite.getGlobalBounds().height);
    centerOrigin(mSprite);
    mType = Road::Railways;
}