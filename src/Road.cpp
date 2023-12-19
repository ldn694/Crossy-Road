#include "Road.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
// Road::Road(Textures::ID ID, const TextureHolder& textures, Road::Type type)
// {
//     mSprite.setTexture(textures.get(ID));
//     mSprite.setScale(WITDH_SIZE / mSprite.getGlobalBounds().width, HEIGHT_SIZE / mSprite.getGlobalBounds().height);
//     centerOrigin(mSprite);
//     mType = Road::Railways;
// }

Road::Road(Textures::ID ID, const TextureHolder& textures, Road::Type type, Zone::Safety safety)
{
    mSprite.setTexture(textures.get(ID));
    setSize(mSprite, sf::Vector2f(WITDH_SIZE, HEIGHT_SIZE));
    centerOrigin(mSprite);
    mType = type;
    mSafety = safety;
    for (int i = MIN_ZONE_ID; i <= MAX_ZONE_ID; i++) {
        std::unique_ptr<Zone> zone(new Zone(safety, sf::FloatRect(i * WITDH_SIZE / NUM_ZONE, -HEIGHT_SIZE / 2.0f, WITDH_SIZE / NUM_ZONE, HEIGHT_SIZE)));
        mZones.push_back(zone.get());
        requestAttach(std::move(zone));
    }
}

sf::FloatRect Road::getHitbox() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

Entity* Road::nearestZone(sf::Vector2f position, Zone::Safety safety)
{
    float minDistance = std::numeric_limits<float>::max();
    Zone* nearest = nullptr;
    for (auto& zone : mZones) {
        float distance = squaredDistance(zone->getWorldPosition(), position);
        if (distance < minDistance && zone->getSafety() == safety) {
            minDistance = distance;
            nearest = zone;
        }
    }
    return nearest;
}