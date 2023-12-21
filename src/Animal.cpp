#include "Animal.hpp"
#include "Category.hpp"
#include "Utility.hpp"
#include "GameStatus.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Animal::Animal(Type type, TextureHolder& textures, SceneNode* tmpNode)
    : mType(type)
    , mTextures(textures)
    , mDirection(Down)
    , tmpNode(tmpNode)
{
    changeDirection(Down);
}

void Animal::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
    //draw hitbox
    sf::FloatRect rect = getHitbox();
    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1);
    shape.setPosition(rect.left, rect.top);
    target.draw(shape);
}

sf::FloatRect Animal::getHitbox() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int Animal::getCategory() const
{
    return Category::Player;
}

Textures::ID Animal::toTextureID(Type type, Direction direction) 
{
    //No general return
    switch (type) {
        case Cat:
            switch (direction) {
                case Left:
                    return Textures::CatLeft;
                case Right:
                    return Textures::CatRight;
                case Up:
                    return Textures::CatUp;
                case Down:
                    return Textures::CatDown;
            }
        case Chicken:
            switch (direction) {
                case Left:
                    return Textures::ChickenLeft;
                case Right:
                    return Textures::ChickenRight;
                case Up:
                    return Textures::ChickenUp;
                case Down:
                    return Textures::ChickenDown;
            }
        case Zebra:
            switch (direction) {
                case Left:
                    return Textures::ZebraLeft;
                case Right:
                    return Textures::ZebraRight;
                case Up:
                    return Textures::ZebraUp;
                case Down:
                    return Textures::ZebraDown;
            }
        case Pig:
            switch (direction) {
                case Left:
                    return Textures::PigLeft;
                case Right:
                    return Textures::PigRight;
                case Up:
                    return Textures::PigUp;
                case Down:
                    return Textures::PigDown;
            }
        case Fox:
            switch (direction) {
                case Left:
                    return Textures::FoxLeft;
                case Right:
                    return Textures::FoxRight;
                case Up:
                    return Textures::FoxUp;
                case Down:
                    return Textures::FoxDown;
            }
    }
}

void Animal::updateCurrent(sf::Time dt)
{
    Entity::updateCurrent(dt);
    if (isMoving && !pendingAnimation()) {
        isMoving = false;
        assertThrow(this->getParent() != nullptr, "Animal has no parent");
        SceneNode* parent = this->getParent();
        if (squaredDistance(mTmpOldPosition, getPosition()) < 1) {//unsuccesful move
            std::cout << "unsuccesful move\n";
            switchParent(this, mZone);
            setPosition(mOldPosition);
        }
        else {
            std::cout << "succesful move\n";
            switchParent(this, mNextZone);
            setPosition(0, 0);
            mZone = mNextZone;
        }
    }
}

bool Animal::addAnimalAnimation(Zone* zone, sf::Time duration, sf::Vector2f offset)
{
    if (pendingAnimation()) {
        return false;
    }
    SceneNode* parent = this->getParent();
    assertThrow(this->getParent() != nullptr, "Animal has no parent");
    mNextZone = zone;
    mOldPosition = getPosition();
    sf::Vector2f newTmpPosition = parent->getWorldPosition() - tmpNode->getWorldPosition() + getPosition();
    mTmpOldPosition = newTmpPosition;
    switchParent(this, tmpNode);
    setPosition(newTmpPosition);
    addDynamicAnimation(zone, duration, offset);
    isMoving = true;
    return true;
}

void Animal::changeDirection(Direction direction)
{
    mDirection = direction;
    mSprite.setTexture(mTextures.get(toTextureID(mType, direction)));
    setSize(mSprite, sf::Vector2f(45, 45));
    centerOrigin(mSprite);
}

void setZone(Animal* player, Zone* zone)
{
    player->mZone = zone;
}

void Animal::move(Direction direction)
{
    float step = 70.f;
    sf::Time duration = sf::seconds(0.5f);
    Road* nextRoad = nullptr;
    sf::Vector2f offset;
    switch (direction) {
        case Animal::Direction::Left:
            nextRoad = static_cast<Road*>(mZone->getParent());
            offset = sf::Vector2f(-step, 0.f);
            break;
        case Animal::Direction::Right:
            nextRoad = static_cast<Road*>(mZone->getParent());
            offset = sf::Vector2f(step, 0.f);
            break;
        case Animal::Direction::Up:
            nextRoad = static_cast<Road*>(mZone->getParent())->mNextRoad;
            offset = sf::Vector2f(0.f, -step);
            break;
        case Animal::Direction::Down:
            nextRoad = static_cast<Road*>(mZone->getParent())->mPreviousRoad;
            offset = sf::Vector2f(0.f, step);
            break;
        default:
            break;
    }
    if (nextRoad == nullptr) {
        return;
    }
    Zone* nextSafeZone = nextRoad->nearestZone(getWorldPosition() + offset, Zone::Safe);
    Zone* nextUnsafeZone = nextRoad->nearestZone(getWorldPosition() + offset, Zone::Unsafe);
    if (nextSafeZone != nullptr) {
        float distanceToSafe = squaredDistance(nextSafeZone->getWorldPosition(), getWorldPosition() + offset);
        if (distanceToSafe < 2 * step * step) {
            if (addAnimalAnimation(nextSafeZone, duration)) {
                changeDirection(direction);
            }
        }
        return;
    }
    assertThrow(nextUnsafeZone != nullptr, "No unsafe zone");
    if (addAnimalAnimation(nextUnsafeZone, duration)) {
        changeDirection(direction);
    }
    // if (addStaticAnimation(offset, duration)) {
    //     changeDirection(direction);
    // }

}