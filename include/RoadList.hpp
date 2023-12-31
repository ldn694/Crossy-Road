#pragma once

#include <SFML/Graphics/View.hpp>

#include "Difficulty.hpp"
#include "Animal.hpp"
#include "Road.hpp"
#include "ResourceIdentifiers.hpp"

class RoadList: public SceneNode{
public:
                            RoadList(const TextureHolder& textures, sf::View& view, int numRoads, std::vector <Animal*> players, Difficulty difficulty, SceneNode* tmpNode);
    // Road*                   getFirstRoad();
    // Road*                   getLastRoad();
    virtual void            updateCurrent(sf::Time dt);
    template <typename T>
    void                    registerRoad(Road::Type roadType);
    void                    setPlayerSpeedMultiplier(float multiplier);  
    const int NUM_ROAD_LEVEL_UP = 40;
private:
    std::pair <Road::Type, int> getNextRoadInfo(int i);

    template <typename T>
    void                    push_back(std::unique_ptr<T> road);
    void                    pop_front();
    Road::Type              getNextType();
    void                    setDifficulty(Difficulty difficulty);
private:
    Road::Type                                                              pre;
    Road*                                                                   curRoad;
    Road*                                                                   firstRoad;
    Road*                                                                   lastRoad;
    SceneNode*                                                              mTmpNode;
    sf::View&                                                               mView;
    std::map<Road::Type, std::function<std::unique_ptr<Road>(int)>>	        mFactories;
    const TextureHolder&                                                    mTextures;
    sf::Time                                                                mPeriod;
    std::vector <Animal*>                                                   mPlayers;
    Difficulty                                                              mDifficulty;
    int                                                                     mPassedRoad;
    float                                                                   mPlayerSpeedMultiplier;
};

template <typename T>
void RoadList::push_back(std::unique_ptr<T> road)
{
    //double linked list
    if (lastRoad != nullptr) {
        lastRoad->mNextRoad = road.get();
        road->mPreviousRoad = lastRoad;
    }
    lastRoad = road.get();
    if (firstRoad == nullptr) {
        firstRoad = road.get();
    }
    requestAttachAtFront(std::move(road));
}

template <typename T>
void RoadList::registerRoad(Road::Type roadType)
{
   // Create a lambda function that returns a new instance of T
    auto factoryFunction = [this](int variant) -> std::unique_ptr<Road> {
        return std::make_unique<T>(mTextures, mDifficulty, variant);
    };

    // Register the factory function for the specified road type
    mFactories[roadType] = factoryFunction;
}

