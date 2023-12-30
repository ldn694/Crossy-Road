#pragma once
#include "Context.hpp"
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"
#include "Car.hpp"
#include "StopLight.hpp"

class SRoad : public Road{
public:
    enum Variant{
        LeftToRight,
        RightToLeft,
        NumSRoadVariants
    };
private:
    int movementSign;
    SceneNode* mediateNode;
    const int maximumCar = 5;
    sf::Time mPeriod;
    sf::Time mTimeSinceLastSpawn;
    const TextureHolder& textures;
    std::vector <Car*> cars;
    // Car::Type carType;
    StopLight* stopLight;
    sf::Time mStopLightTimer;;
    const sf::Time mStopLightPeriod[StopLight::State::NumStopLightState] = {sf::seconds(2.0f), sf::seconds(1.0f), sf::seconds(2.5f)};
private:
    Car* addCar(Car::Type carType, sf::Vector2f position);
public:
    ~SRoad();
    SRoad(Context context, const TextureHolder& textures, Difficulty difficulty, int variant);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};

