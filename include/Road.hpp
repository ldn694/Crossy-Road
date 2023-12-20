#pragma once
#include "Entity.hpp"
#include "Zone.hpp"
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
    const float WITDH_SIZE = 1050;
    const float HEIGHT_SIZE = 50;
    const float NUM_ZONE = 15;
    Road*                      mNextRoad;
    Road*                      mPreviousRoad;

public:
                    Road(Textures::ID ID, const TextureHolder& textures, Road::Type type, Zone::Safety safety);
    virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    sf::FloatRect   getHitbox() const;
    Zone*           nearestZone(sf::Vector2f position, Zone::Safety safety);
    Zone*           randomZone(Zone::Safety safety);
    template <typename T>
    T*              addZone(std::unique_ptr<T> zone);
    template <typename T>
    T*              addEntity(std::unique_ptr<T> zone);
    Zone::Safety    getSafety() const;

protected:
    sf::Sprite                 mSprite;
    Road::Type                 mType;
    Zone::Safety               mSafety;
    std::vector<Zone*>         mZones;
    std::vector<Entity*>       mEntities;
};

template <typename T>
T* Road::addZone(std::unique_ptr<T> zone)
{
    mZones.push_back(zone.get());
    requestAttach(std::move(zone));
}

template <typename T>
T* Road::addEntity(std::unique_ptr<T> entity)
{
    mEntities.push_back(entity.get());
    requestAttach(std::move(entity));
}