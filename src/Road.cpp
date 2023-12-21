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

Road::Road(Textures::ID ID, const TextureHolder& textures, Road::Type type, Zone::Safety safety, Difficulty difficulty)
{
    mSprite.setTexture(textures.get(ID));
    setSize(mSprite, sf::Vector2f(WITDH_SIZE, HEIGHT_SIZE));
    setOrigin(0, 0);
    mType = type;
    mSafety = safety;
    for (int i = 0; i < NUM_ZONE; i++) {
        std::unique_ptr<Zone> zone(new Zone(safety, sf::FloatRect(i * WITDH_SIZE / NUM_ZONE, 0, WITDH_SIZE / NUM_ZONE, HEIGHT_SIZE), this));
        mZones.push_back(zone.get());
        requestAttach(std::move(zone));
    }
}

sf::FloatRect Road::getHitbox() const
{
    return getWorldTransform().transformRect(mSprite.getLocalBounds());
}

Zone* Road::nearestZone(sf::Vector2f position, Zone::Safety safety)
{
    float minDistance = 10000.0f;
    Zone* nearest = nullptr;
    for (auto& zone : mZones) {
        float distance = squaredDistance(zone->getWorldPosition(), position);
        if ((nearest == nullptr || distance < minDistance) && zone->getSafety() == safety) {
            minDistance = distance;
            nearest = zone;
        }
    }
    return nearest;
}

Zone* Road::randomZone(Zone::Safety safety)
{
    std::vector<Zone*> zones;
    for (auto& zone : mZones) {
        if (zone->getSafety() == safety) {
            zones.push_back(zone);
        }
    }
    assertThrow(!zones.empty(), "No zone of this safety type");
    int index = rand() % zones.size();
    // std::cerr << zones.size() << " " << index << "\n";
    return zones[index];
}

Zone::Safety Road::getSafety() const
{
    return mSafety;
}

void Road::addZone(Zone* zone)
{
    mZones.push_back(zone);
    // std::cerr << "added zone " << mZones.size() << "\n";
}

void Road::removeZone(Zone* zone)
{
    auto found = std::find_if(mZones.begin(), mZones.end(), [&](Zone* z) { return z == zone; });
    assertThrow(found != mZones.end(), "Zone not found");
    mZones.erase(found);
}