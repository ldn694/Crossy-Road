#pragma once
#include "Context.hpp"
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"
#include "FloatingLog.hpp"

class River : public Road{
public:
    enum Variant{
        LeftToRight,
        RightToLeft,
        Stable,
        NumRiverVariants
    };
private:
    int movementSign;
    SceneNode* mediateNode;
    const int maximumLog = 7;
    sf::Time mPeriod;
    sf::Time mTimeSinceLastSpawn;
    const TextureHolder& textures;
    std::vector <FloatingLog*> logs;
private:
    FloatingLog* addLog(FloatingLog::Type logType, sf::Vector2f position);
public:
    ~River();
    River(Context context, const TextureHolder& textures, Difficulty difficulty, int variant);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};

