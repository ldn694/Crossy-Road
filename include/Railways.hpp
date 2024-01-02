#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"
#include "Train.hpp"
#include "TrafficLight.hpp"
#include "Context.hpp"
#include "SFML/System/Clock.hpp"
class Railways : public Road{
public:
    enum Variant {
        LeftToRight,
        RightToLeft,
        NumRailwaysVariants,
    };
private:
    int movementSign;
    SceneNode* mediateNode;
    sf::Time mPeriod, mBeginTime;
    float mSpeed;
    sf::Time mTimeSinceLastSpawn;
    sf::Clock   mClock;
    const TextureHolder& textures;
    SoundPlayer& soundPlayer;
    Train*  train;
    TrafficLight* light;
    bool checkBegin, isComing;
    sf::Sound *mTrainIncomingSound;

private:
    Train* addTrain(sf::Vector2f position);
    TrafficLight* addLight(sf::Vector2f position);
public:
    ~Railways();
    Railways(Context context, const TextureHolder& textures, SoundPlayer& sounds, Difficulty difficulty, int variant);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};

