#include "Road.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
Road::Road(Textures::ID ID, const TextureHolder& textures, Road::Type type)
{
    mSprite.setTexture(textures.get(ID));
    mSprite.setScale(WITDH_SIZE / mSprite.getGlobalBounds().width, HEIGHT_SIZE / mSprite.getGlobalBounds().height);
    centerOrigin(mSprite);
    setHitboxSize(sf::Vector2f(WITDH_SIZE, HEIGHT_SIZE));
    mType = Road::Railways;
}