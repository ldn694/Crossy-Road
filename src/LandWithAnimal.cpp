#include "LandWithAnimal.hpp"
#include "WalkingAnimal.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <time.h>
#include <stdlib.h>

WalkingAnimal::Type toType(LandWithAnimal::Variant variant){
    switch (variant)
    {
    case LandWithAnimal::Pig:
        return WalkingAnimal::Pig;
    case LandWithAnimal::Lion:
        return WalkingAnimal::Lion;
    case LandWithAnimal::Fox:
        return WalkingAnimal::Fox;
    default:
        break;
    }
}
LandWithAnimal::LandWithAnimal(const TextureHolder& textures, Difficulty difficulty, int variant) : Road(Textures::NormalLand, textures, Road::Type::LandWithAnimal, Zone::Safety::Safe, difficulty){
    std::unique_ptr<SceneNode> mediate(new SceneNode());
    mediateNode = mediate.get();
    requestAttach(std::move(mediate));
    sf::Vector2f position = sf::Vector2f( 100 + rand() % (1040 - 200), HEIGHT_SIZE / 2 - 20) - mediateNode->getPosition();
    std::unique_ptr<WalkingAnimal> curAnimal(new WalkingAnimal(toType(static_cast<LandWithAnimal::Variant>(variant)), position, textures, this));
    animal = curAnimal.get();
    curAnimal->setPosition(position);
    mediateNode->requestAttach(std::move(curAnimal));
    mediateNode->attachChildren();

    mClock.restart();
    mChangeStateClock.restart();
    curStatus = 1;
    curDirection = 1  - (rand() % 2)*2;
    animal->ChangeState(curDirection);
}
void LandWithAnimal::updateCurrent(sf::Time dt)
{
    Road::updateCurrent(dt);
    if (animal->getWorldPosition().x < 0 || animal->getWorldPosition().x + animal->getHitbox().width > WITDH_SIZE) {
        curDirection =  -curDirection;
    }
    if (mClock.getElapsedTime() > mTime[curStatus]) {
        mClock.restart();
        curStatus = 1 - curStatus;
    }
    if (curStatus && mChangeStateClock.getElapsedTime() > sf::seconds(0.3f)) {
        mChangeStateClock.restart();
        animal->ChangeState(curDirection);
    }
    mediateNode->move(dt.asSeconds() * 50 * curStatus * curDirection, 0);
}
void LandWithAnimal::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
