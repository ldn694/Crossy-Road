#include "SRoad.hpp"
#include "Utility.hpp"
#include "FloatingLog.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Textures::ID toTextureID()
{
    int typeList[3] = {Textures::SRoad_Default, Textures::SRoad_Line, Textures::SRoad_Stripe};
    return static_cast<Textures::ID>(typeList[rand() % 3]);
}

Car::Type getRandCarType(int movementSign) {
    if (movementSign == 1) {
        int typeList[4] = {Car::RedCarRight, Car::BlueCarRight, Car::VanRight, Car::TruckRight};
        return static_cast<Car::Type>(typeList[rand() % 4]);
    } 
    else {
        int typeList[4] = {Car::RedCarLeft, Car::BlueCarLeft, Car::VanLeft, Car::TruckLeft};
        return static_cast<Car::Type>(typeList[rand() % 4]);
    }

}

SRoad::SRoad(const TextureHolder& textures, Difficulty difficulty, int variant) : Road(toTextureID(), textures, Road::Type::SRoad, Zone::Safety::Safe, difficulty), textures(textures) {
    sf::Time basePeriodTime = sf::seconds(2.5f);
    int numPartionPeriod;
    switch (difficulty) {
    case Difficulty::Easy:
        numPartionPeriod = Rand(80, 90);
        break;
    case Difficulty::Medium:
        numPartionPeriod = Rand(60, 70);
        break;
    case Difficulty::Hard:
        numPartionPeriod = Rand(40, 50);
        break;
    }
    mPeriod = basePeriodTime * (numPartionPeriod / 100.f);
    switch (variant) {
    case SRoad::LeftToRight:
        movementSign = 1;
        break;
    case SRoad::RightToLeft:
        movementSign = -1;
        break;
    default:
        movementSign = 0;
        break;
    }

    mStopLightTimer = sf::Time::Zero;
    const int numPartionPeriodStopLight = 10;
    mStopLightTimer += float(rand() % numPartionPeriodStopLight / numPartionPeriodStopLight) * mStopLightPeriod[StopLight::State::Red];


    std::unique_ptr<SceneNode> mediate(new SceneNode());
    mediateNode = mediate.get();
    requestAttach(std::move(mediate));
    mTimeSinceLastSpawn = sf::Time::Zero;
    float minimumDistance = (WITDH_SIZE - maximumCar * 50) / (maximumCar - 1);
    int numCar = movementSign == 0 ? 7 : 3;
    float x = rand() % (int)minimumDistance, y = (HEIGHT_SIZE - 50) / 2;

    for (int i = 0; i < numCar; i++) {
        Car::Type carType = getRandCarType(movementSign);
        float offsetToNextCar = rand() % (int)minimumDistance;
        Car* car = addCar(carType, sf::Vector2f(x, y));
        float newX = x + car->getHitbox().width + minimumDistance + offsetToNextCar;
        x = newX;
    }

    std::unique_ptr<StopLight> stopLightPtr(new StopLight(sf::Vector2f(200, HEIGHT_SIZE), textures, this));
    stopLight = stopLightPtr.get();
    float xStopLight;
    switch (variant) {
    case SRoad::LeftToRight:
        xStopLight = WITDH_SIZE / 2;
        break;
    case SRoad::RightToLeft:
        xStopLight = WITDH_SIZE / 2;
        break;
    default:
        xStopLight = 0;
        break;
    }
    stopLight->setPosition(sf::Vector2f(xStopLight, HEIGHT_SIZE));
    requestAttach(std::move(stopLightPtr));

    attachChildren();
    mediateNode->attachChildren();
}

SRoad::~SRoad() {
    // std::cerr << "---------------------\n";
    // std::cerr << "River destroyed\n";
    // for (int i = 0; i < zones.size(); i++) {
    //     mediateNode->requestDetach(zones[i]->getParent());
    // }
}

Car* SRoad::addCar(Car::Type carType, sf::Vector2f position)
{
    std::unique_ptr<Car> car(new Car(carType, position, textures, this));
    cars.push_back(car.get());
    car->setPosition(position);
    Car* carPtr = car.get();
    mediateNode->requestAttach(std::move(car));
    return carPtr;
}

void SRoad::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

float getSpeedMultiplier(StopLight::State state) {
    switch (state) {
    case StopLight::Red:
        return 0;
    case StopLight::Yellow:
        return 0.8f;
    case StopLight::Green:
        return 1;
    default:
        return 0;
    }
}

void SRoad::updateCurrent(sf::Time dt)
{
    Road::updateCurrent(dt);

    mStopLightTimer += dt;
    if (mStopLightTimer > mStopLightPeriod[stopLight->getState()]) {
        mStopLightTimer = sf::Time::Zero;
        stopLight->changeState();
    }

    float speedMultiplier = getSpeedMultiplier(stopLight->getState());

    if (movementSign != 0 && stopLight->getState() != StopLight::Red) {
        mTimeSinceLastSpawn += dt;
    }
    while (true) {
        int index = -1;
        for (int i = 0; i < cars.size(); i++) {
            if ((cars[i]->getWorldPosition().x + cars[i]->getHitbox().width < 0 && movementSign == -1) || (cars[i]->getWorldPosition().x > WITDH_SIZE && movementSign == 1)) {
                index = i;
                break;
            }
        }
        if (index == -1) break;
        Car* car = cars[index];
        cars.erase(cars.begin() + index);
        mediateNode->requestDetach(car);
    }
    if (mTimeSinceLastSpawn > mPeriod) {
        mTimeSinceLastSpawn = sf::Time::Zero;
        sf::Vector2f position;
        if (movementSign == 1) {
            position = sf::Vector2f(-150 - (rand() % 50), (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();
        }
        else {
            position = sf::Vector2f(WITDH_SIZE + (rand() % 50), (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();

        }
        Car::Type carType = getRandCarType(movementSign);
        addCar(carType, position);
        mediateNode->attachChildren();
    }
    mediateNode->move(dt / mPeriod * 300 * movementSign * speedMultiplier, 0);
}