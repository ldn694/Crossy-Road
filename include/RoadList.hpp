#pragma once

#include <SFML/Graphics/View.hpp>

#include "Animal.hpp"
#include "Road.hpp"
#include "ResourceIdentifiers.hpp"

class RoadList: public SceneNode{
public:
                            RoadList(const TextureHolder& textures, sf::View view, int numRoads, sf::Time period);
    // Road*                   getFirstRoad();
    // Road*                   getLastRoad();
    virtual void            updateCurrent(sf::Time dt);
    template <typename T>
    void                    registerRoad(Road::Type roadType);
private:
    template <typename T>
    void                    push_back(std::unique_ptr<T> road);
    void                    pop_front();
    Road::Type              getNextType();
private:
    Road*                                                           curRoad;
    Road*                                                           firstRoad;
    Road*                                                           lastRoad;
    sf::View                                                        mView;
    std::map<Road::Type, std::function<std::unique_ptr<Road>()>>	mFactories;
    const TextureHolder&                                            mTextures;
    sf::Time                                                        mPeriod;
    sf::Time                                                        mTimeSinceLastUpdate;
};

template <typename T>
void RoadList::push_back(std::unique_ptr<T> road)
{
    //double linked list
    if (lastRoad != nullptr)
    {
        lastRoad->mNextRoad = road.get();
        road->mPreviousRoad = lastRoad;
        lastRoad = road.get();
        lastRoad->mNextRoad = nullptr;
    }
    else {
        firstRoad = road.get();
        lastRoad = road.get();
    }
    requestAttach(std::move(road));
}

template <typename T>
void RoadList::registerRoad(Road::Type roadType)
{
   // Create a lambda function that returns a new instance of T
    auto factoryFunction = [this]() -> std::unique_ptr<Road> {
        return std::make_unique<T>(mTextures);
    };

    // Register the factory function for the specified road type
    mFactories[roadType] = factoryFunction;
}

