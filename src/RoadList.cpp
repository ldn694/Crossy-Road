#include "RoadList.hpp"
#include "Railways.hpp"
#include "River.hpp"
#include "SRoad.hpp"
#include "Land.hpp"
#include <stdlib.h>
#include <time.h> 


Road::Type RoadList::getNextType()
{
    int type = rand() % Road::TypeCount;
    return static_cast<Road::Type>(type);
}

RoadList::RoadList(const TextureHolder& textures, sf::View view, int numRoads, sf::Time period): mTextures(textures), mPeriod(period), mView(view)
{
    registerRoad<Railways>(Road::Railways);
	registerRoad<River>(Road::River);
	registerRoad<SRoad>(Road::SRoad);
	registerRoad<Land>(Road::Land);
    srand(time(NULL));
    if (numRoads < 1) return;
    firstRoad = nullptr;
    lastRoad = nullptr;
    for (int i = 0; i < numRoads; i++)
    {
        Road::Type type = getNextType();
        std::unique_ptr<Road> road = mFactories[type]();
        road->setPosition(0, -(i - 2) * road->Road::HEIGHT_SIZE);
        push_back(std::move(road));
    }
    mTimeSinceLastUpdate = sf::Time::Zero;
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