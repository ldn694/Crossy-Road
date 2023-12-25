#include "Railways.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>


Railways::~Railways(){

}
Railways::Railways(const TextureHolder& textures, Difficulty difficulty, int variant) : 
    Road(Textures::Railways, textures, Road::Type::Railways, Zone::Safety::Safe, difficulty),
    textures(textures)
{
    sf::Time basePeriodTime = sf::seconds(5.f);
    
    float baseSpeed = 3500;
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
    mSpeed = baseSpeed * (100.f / numPartionPeriod);
    mBeginTime = sf::seconds(2.5f) * (Rand(50,100) / 100.f) * (numPartionPeriod / 100.f);
    switch (variant) {
    case Railways::LeftToRight:
        movementSign = 1;
        break;
    case Railways::RightToLeft:
        movementSign = -1;
        break;
    default:
        movementSign = 0;
        break;
    }
    std::unique_ptr<SceneNode> mediate(new SceneNode());
    mediateNode = mediate.get();
    requestAttach(std::move(mediate));
    mTimeSinceLastSpawn = sf::Time::Zero;
    sf::Vector2f position;
    if (movementSign == 1) {
        position = sf::Vector2f(WITDH_SIZE * 0.2, (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();
    }
    else {
        position = sf::Vector2f(WITDH_SIZE * 0.8, (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();
    }
    addLight(position);
    
    attachChildren();
    mediateNode->attachChildren();
    isTrain = false;
    checkBegin = false;


}
void Railways::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
TrafficLight* Railways::addLight(sf::Vector2f position)
{
    std::unique_ptr<TrafficLight> curLight(new TrafficLight(position, textures, this));
    light = curLight.get();
    curLight->setPosition(position);
    TrafficLight* lightPtr = curLight.get();
    addEntity(std::move(curLight));
    return lightPtr;
}
Train* Railways::addTrain(sf::Vector2f position)
{
    std::unique_ptr<Train> curTrain(new Train(position, textures, this));
    train = curTrain.get();
    isTrain = true;
    curTrain->setPosition(position);
    Train* trainPtr = curTrain.get();
    mediateNode->requestAttach(std::move(curTrain));
    return trainPtr;
}
void Railways::updateCurrent(sf::Time dt)
{
    Road::updateCurrent(dt);

    if (movementSign != 0) {
        mTimeSinceLastSpawn += dt;
    }
    
    if (checkBegin && mPeriod - mTimeSinceLastSpawn < sf::seconds(1.0f)) {
        isComing = true;
        mClock.restart();
        light->changeColor();
    }
    else{
        isComing = false;
        light->setDefaultColor();
    }

    if (isTrain && ((train->getWorldPosition().x + train->getHitbox().width < 0 && movementSign == -1) || (train->getWorldPosition().x > WITDH_SIZE && movementSign == 1))){
        mediateNode->requestDetach(train);
        train = nullptr;
        isTrain = false;
    }
    if (!checkBegin && mTimeSinceLastSpawn > mBeginTime) {
        mTimeSinceLastSpawn = sf::Time::Zero;
        checkBegin = true;
    }   
    
    if (isComing && mClock.getElapsedTime().asSeconds() > 0.2){
        mClock.restart();
        light->changeColor();
    }
    if (checkBegin && mTimeSinceLastSpawn > mPeriod) {
        mTimeSinceLastSpawn = sf::Time::Zero;
        sf::Vector2f position;
        if (movementSign == 1) {
            position = sf::Vector2f(-1800, (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();
        }
        else {
            position = sf::Vector2f(WITDH_SIZE + 1000, (HEIGHT_SIZE - 50) / 2) - mediateNode->getPosition();
        }
        addTrain(position);
        mediateNode->attachChildren();
    }
    
    if (isTrain) mediateNode->move(dt / mPeriod * mSpeed * movementSign, 0);
}
