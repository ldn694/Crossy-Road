#pragma once
#include "Difficulty.hpp"
#include "Entity.hpp"
#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"
#include <SFML/Graphics/Sprite.hpp>

const bool NO_ATTACHING = false;

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
    const float HEIGHT_SIZE = 65;
    const float NUM_ZONE = 15;
    Road*                      mNextRoad;
    Road*                      mPreviousRoad;

public:
                    Road(Textures::ID ID, const TextureHolder& textures, Road::Type type, Zone::Safety safety, Difficulty difficulty);
    virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    sf::FloatRect   getHitbox() const;
    Zone*           nearestZone(sf::Vector2f position, Zone::Safety safety);
    Zone*           randomZone(Zone::Safety safety);
    template <typename T>
    T*              addZone(std::unique_ptr<T> zone);
    void            addZone(Zone* zone);
    void            removeZone(Zone* zone);
    template <typename T>
    T*              addEntity(std::unique_ptr<T> zone);
    Zone::Safety    getSafety() const;
    bool            visit();

protected:
    sf::Sprite                 mSprite;
    Road::Type                 mType;
    Zone::Safety               mSafety;
    std::vector<Zone*>         mZones;
    std::vector<Entity*>       mEntities;
    bool                       mVisited;
};

template <typename T>
T* Road::addZone(std::unique_ptr<T> zone)
{
    T* temp = zone.get();
    mZones.push_back(zone.get());
    requestAttach(std::move(zone));
    return temp;
}

template <typename T>
T* Road::addEntity(std::unique_ptr<T> entity)
{
    T* temp = entity.get();
    mEntities.push_back(entity.get());
    requestAttach(std::move(entity));
    return temp;
}