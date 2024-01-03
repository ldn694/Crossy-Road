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
        return Railways::NumRailwaysVariants;
    case Road::River:
        return River::NumRiverVariants;
    case Road::SRoad:
        return SRoad::NumSRoadVariants;
    case Road::Land:
        return Land::NumLandVariants;
    }
    return 0;
}

void RoadList::setDifficulty(Difficulty difficulty)
{
    mDifficulty = difficulty;
    std::cerr << "setDifficulty: " << int(mDifficulty) << "\n";
    switch (mDifficulty) {
        case Easy:
            mPeriod = sf::seconds(1.0f);
            for (int i = 0; i < mPlayers.size(); i++) {
                mPlayers[i]->setMovementDuration(sf::seconds(0.15f) / mPlayerSpeedMultiplier);
            }
            break;
        case Medium:
            mPeriod = sf::seconds(0.7f);
            for (int i = 0; i < mPlayers.size(); i++) {
                mPlayers[i]->setMovementDuration(sf::seconds(0.15f) / mPlayerSpeedMultiplier);
            }
            break;
        case Hard:
            mPeriod = sf::seconds(0.5f);
            for (int i = 0; i < mPlayers.size(); i++) {
                mPlayers[i]->setMovementDuration(sf::seconds(0.15f) / mPlayerSpeedMultiplier);
            }
            break;
        default:
            for (int i = 0; i < mPlayers.size(); i++) {
                mPlayers[i]->setMovementDuration(sf::seconds(0.15f) / mPlayerSpeedMultiplier);
            }
    }
}

void RoadList::setPlayerSpeedMultiplier(float multiplier)
{
    mPlayerSpeedMultiplier = multiplier;
    setDifficulty(mDifficulty);
}

std::pair <Road::Type, int> RoadList::getNextRoadInfo(int i = 20) {
    Road::Type type = Road::Land;
    if (i > 5) {
        type = getNextType();
        // type = Road::Railways;
    }
    int variant = rand() % getNumType(type);
    if (type == Road::Land) {
        if (pre != Road::Land) {
            variant = Land::Start;
        }
        else {
            variant = Land::Normal;
        }
    }
    if (i <= 5) {
        type = Road::Land;
        variant = Land::Empty;
    }
    pre = type;
    return std::make_pair(type, variant);
}

RoadList::RoadList(Context context, const TextureHolder& textures, SoundPlayer& sounds, sf::View& view, int numRoads, std::vector <Animal*> players, Difficulty difficulty, SceneNode* tmpNode)
    : mView(view)
    , mTextures(textures)
    , mPlayers(players)
    , mDifficulty(difficulty)
    , mPlayerSpeedMultiplier(1.0f)
    , mTmpNode(tmpNode)
    , mContext(context)
    , mSounds(sounds)
{
    setDifficulty(difficulty);
    registerRoad<Railways>(Road::Railways);
	registerRoad<River>(Road::River);
	registerRoad<SRoad>(Road::SRoad);
	registerRoad<Land>(Road::Land);
    pre = Road::Land;
    if (numRoads < 1) return;
    firstRoad = nullptr;
    lastRoad = nullptr;
    Road::Type pre = Road::Land;
    for (int i = 0; i < numRoads; i++)
    {
        // while (i == midID && type == Road::River) {
        //     type = getNextType();
        // }
        std::pair <Road::Type, int> pair = getNextRoadInfo(i);
        Road::Type type = pair.first;
        int variant = pair.second;
        std::unique_ptr<Road> road = mFactories[type](variant);
        road->setPosition(0, -i * road->Road::HEIGHT_SIZE);
        push_back(std::move(road));
        pre = type;
    }
    Road* curRoad = firstRoad;
    for (int i = 0; i < 5; i++) {
        curRoad->visit();
        curRoad = curRoad->mNextRoad;
    }
    curRoad->visit();
    Zone* startZoneList[2];
    startZoneList[0] = curRoad->randomZone(Zone::Safe);
    do {
        startZoneList[1] = curRoad->randomZone(Zone::Safe);
    } while (startZoneList[0] == startZoneList[1]);
    for (int i = 0; i < players.size(); i++) {
        switchParent(players[i], startZoneList[i % 2]);
        setZone(players[i], startZoneList[i % 2]);
    }
    mPassedRoad = 0;
}

void RoadList::updateCurrent(sf::Time dt)
{
    if (lastRoad->getParent() == this && firstRoad->getWorldPosition().y > mView.getCenter().y + mView.getSize().y / 2 + firstRoad->HEIGHT_SIZE / 2) {
        pop_front();
        std::pair <Road::Type, int> pair = getNextRoadInfo();
        Road::Type type = pair.first;
        int variant = pair.second;
        std::unique_ptr<Road> road = mFactories[type](variant);
        road->setPosition(0, lastRoad->getPosition().y - lastRoad->HEIGHT_SIZE);
        push_back(std::move(road));
        mPassedRoad++;
        if (mPassedRoad % NUM_ROAD_LEVEL_UP == 0 && mPassedRoad != 0) {
            setDifficulty(static_cast<Difficulty>(std::min(int(mDifficulty + 1), int(Difficulty::NumDifficulties) - 1)));
        }
    }
    move(0, dt / mPeriod * firstRoad->HEIGHT_SIZE);
    mTmpNode->move(0, dt / mPeriod * firstRoad->HEIGHT_SIZE);
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