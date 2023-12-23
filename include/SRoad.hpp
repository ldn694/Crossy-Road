#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"
#include "Car.hpp"

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
private:
    Car* addCar(Car::Type carType, sf::Vector2f position);
public:
    ~SRoad();
    SRoad(const TextureHolder& textures, Difficulty difficulty, int variant);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};

