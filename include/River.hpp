#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"
#include "FloatingLog.hpp"

class River : public Road{
private:
    int movementSign;
    SceneNode* mediateNode;
    const int maximumLog = 5;
    sf::Time mPeriod;
    sf::Time mTimeSinceLastSpawn;
    const TextureHolder& textures;
    std::vector <Zone*> zones;
private:
    FloatingLog* addLog(FloatingLog::Type logType, sf::Vector2f position);
public:
    River(const TextureHolder& textures, Difficulty difficulty);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};

