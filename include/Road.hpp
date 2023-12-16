#pragma once
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include <SFML/Graphics/Sprite.hpp>

class Road : public Entity{

public:
    enum Type{
        Railways,
        SRoad,
        River,
        Land,
        TypeCount
    };
    Road(Textures::ID ID, const TextureHolder& textures, Road::Type type);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    sf::FloatRect getHitbox() const;

protected:
    float WITDH_SIZE = 640;
    float HEIGHT_SIZE = 50;
    sf::Sprite                 mSprite;
    Road::Type                 mType;
};