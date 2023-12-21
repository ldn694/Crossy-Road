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
    int midID = numRoads / 2;
    for (int i = 0; i < numRoads; i++)
    {
        // while (i == midID && type == Road::River) {
        //     type = getNextType();
        // }
        Road::Type type = Road::Land;
        if (i > 0) {
            type = getNextType();
        }
        std::unique_ptr<Road> road = mFactories[type]();
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
        std::unique_ptr<Road> road = mFactories[type]();
        road->setPosition(0, lastRoad->getPosition().y - lastRoad->HEIGHT_SIZE);
        push_back(std::move(road));
    }
    move(0, dt / mPeriod * firstRoad->HEIGHT_SIZE);
}

void RoadList::pop_front()
{
    if (firstRoad == nullptr) return;
    Road* tmp = firstRoad;
    firstRoad = firstRoad->mNextRoad;
    firstRoad->mPreviousRoad = nullptr;
    requestDetach(tmp);
}