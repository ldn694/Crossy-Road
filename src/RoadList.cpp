#include "RoadList.hpp"
#include "Railways.hpp"
#include "River.hpp"
#include "SRoad.hpp"
#include "Land.hpp"


Road::Type RoadList::getNextType()
{
    int type = rand() % Road::TypeCount;
    return static_cast<Road::Type>(type);
}

int getNumType(Road::Type type)
{
    switch (type) {
    case Road::Railways:
        return 1;
    case Road::River:
        return River::NumRiverVariants;
    case Road::SRoad:
        return 1;
    case Road::Land:
        return Land::NumLandVariants;
    }
    return 0;
}

void RoadList::addRirvers(int numRivers, const TextureHolder& textures)
{
    //last and first road must not be stable
    for (int i = 0; i < numRivers; i++) {
        Road::Type type = Road::River;
        std::unique_ptr<Road> road = mFactories[type](0);
        road->setPosition(0, lastRoad->getPosition().y - lastRoad->HEIGHT_SIZE);
        push_back(std::move(road));
    }
}

RoadList::RoadList(const TextureHolder& textures, sf::View view, int numRoads, sf::Time period, Animal* player, Difficulty difficulty)
    : mView(view)
    , mTextures(textures)
    , mPeriod(period)
    , mPlayer(player)
    , mDifficulty(difficulty)
{
    registerRoad<Railways>(Road::Railways);
	registerRoad<River>(Road::River);
	registerRoad<SRoad>(Road::SRoad);
	registerRoad<Land>(Road::Land);

    if (numRoads < 1) return;
    firstRoad = nullptr;
    lastRoad = nullptr;
    for (int i = 0; i < numRoads; i++)
    {
        // while (i == midID && type == Road::River) {
        //     type = getNextType();
        // }
        Road::Type type = Road::Land;
        if (i > 0) {
            type = getNextType();
            // type = Road::Land;
        }
        int variant = rand() % getNumType(type);
        if (i == 0) {
            type = Road::Land;
            variant = 0;
        }
        std::unique_ptr<Road> road = mFactories[type](variant);
        road->setPosition(0, -i * road->Road::HEIGHT_SIZE);
        push_back(std::move(road));
    }
    Zone* firstZone = firstRoad->randomZone(Zone::Safe);
    switchParent(player, firstZone);
    setZone(player, firstZone);
}

void RoadList::updateCurrent(sf::Time dt)
{
    if (lastRoad->getParent() == this && firstRoad->getWorldPosition().y > mView.getCenter().y + mView.getSize().y / 2 + firstRoad->HEIGHT_SIZE / 2) {
        pop_front();
        Road::Type type = getNextType();
        std::unique_ptr<Road> road = mFactories[type](0);
        road->setPosition(0, lastRoad->getPosition().y - lastRoad->HEIGHT_SIZE);
        push_back(std::move(road));
    }
    move(0, dt / mPeriod * firstRoad->HEIGHT_SIZE);
}

void RoadList::pop_front()
{
    if (!firstRoad) return;
    if (firstRoad->mNextRoad) {
        firstRoad->mNextRoad->mPreviousRoad = nullptr;
        requestDetach(firstRoad);
        firstRoad = firstRoad->mNextRoad;
    }
}