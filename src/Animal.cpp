#include "Animal.hpp"
#include "Category.hpp"
#include "Utility.hpp"
#include "GameStatus.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Animal::Animal(int playerID, Type type, std::string playerName, TextureHolder& textures,  FontHolder& fonts, SoundPlayer& sounds, SceneNode* tmpNode, int& passedRoad)
    : mType(type)
    , mTextures(textures)
    , mDirection(Down)
    , tmpNode(tmpNode)
    , passedRoad(passedRoad)
    , mPlayerID(playerID)
    , mSounds(sounds)
{
    mPlayerNameText.setFont(fonts.get(Fonts::Bungee));
    mPlayerNameText.setString(playerName);
    mPlayerNameText.setCharacterSize(15);
    mPlayerNameText.setFillColor(sf::Color::White);
    centerOrigin(mPlayerNameText);
    mPlayerNameText.setPosition(0, -40);
    changeDirection(Down, false);
}

void Animal::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
    target.draw(mPlayerNameText, states);
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
    return Category::Player | (mPlayerID == 0 ? Category::PlayerOne : Category::PlayerTwo);
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
        case Lion:
            switch (direction) {
                case Left:
                    return Textures::LionLeft;
                case Right:
                    return Textures::LionRight;
                case Up:
                    return Textures::LionUp;
                case Down:
                    return Textures::LionDown;
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
        Entity* parent = static_cast<Entity*>(this->getParent());
        if (squaredDistance(mTmpOldPosition, getPosition()) < 1) {//unsuccesful move
            // std::cerr << "unsuccesful move\n";
            switchParent(this, mZone);
            setPosition(mOldPosition);
        }
        else {
            // std::cerr << "succesful move\n";
            switchParent(this, mNextZone);
            setPosition(0, 0);
            mZone = mNextZone;
            if (mZone->getSafety() == Zone::Unsafe) {
                // std::cerr << "unsafe zone\n";
                throw GameStatus(GameStatus::GameLost, GameStatus::Drowned, this);
            }
        }
        mSounds.setListenerPosition(getWorldPosition());
    }
    passedRoad += mZone->getRoad()->visit();
}



bool Animal::addAnimalAnimation(Zone* zone, sf::Time duration, sf::Vector2f offset)
{
    if (pendingAnimation()) {
        return false;
    }
    if (zone == mZone) {
        return false;
    }
    SceneNode* parent = this->getParent();
    assertThrow(this->getParent() != nullptr, "Animal has no parent");
    mNextZone = zone;
    Road* curRoad = mZone->getRoad();
    Road* nextRoad = mNextZone->getRoad();
    mOldPosition = getPosition();
    // SceneNode* tmpZone = mZone;
    // if (curRoad != nextRoad) {
    //     tmpZone = tmpNode;
    // }
    SceneNode* tmpZone = tmpNode;
    sf::Vector2f newTmpPosition = parent->getWorldPosition() - tmpZone->getWorldPosition() + getPosition();
    mTmpOldPosition = newTmpPosition;
    switchParent(this, tmpZone);
    setPosition(newTmpPosition);
    addDynamicAnimation(zone, duration, offset);
    isMoving = true;
    return true;
}

void Animal::setMovementDuration(sf::Time duration)
{
    mDuration = duration;
}

void Animal::changeDirection(Direction direction, bool isMoving)
{
    mDirection = direction;
    mSprite.setTexture(mTextures.get(toTextureID(mType, direction)));
    if (isMoving) {
        mSounds.play(SoundEffect::Animal_Jump);
    }
    float width, height;
    switch (direction) {
        case Left:
        case Right:
            width = 45;
            height = 45;
            break;
        case Up:
        case Down:
            width = 42;
            height = 57;
            break;
    }
    setSize(mSprite, sf::Vector2f(width, height));
    centerOrigin(mSprite);
}

void setZone(Animal* player, Zone* zone)
{
    player->mZone = zone;
}

void Animal::move(Direction direction)
{
    if (pendingAnimation()) {
        return;
    }
    float step = 70.f;
    Road* nextRoad = nullptr;
    sf::Vector2f offset;
    switch (direction) {
        case Animal::Direction::Left:
            nextRoad = mZone->getRoad();
            offset = sf::Vector2f(-step, 0.f);
            break;
        case Animal::Direction::Right:
            nextRoad = mZone->getRoad();
            offset = sf::Vector2f(step, 0.f);
            break;
        case Animal::Direction::Up:
            nextRoad = mZone->getRoad()->mNextRoad;
            offset = sf::Vector2f(0.f, -step);
            break;
        case Animal::Direction::Down:
            nextRoad = mZone->getRoad()->mPreviousRoad;
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
    float distanceToSafe = 100000000;
    if (nextSafeZone != nullptr && nextSafeZone != mZone) {
        distanceToSafe = squaredDistance(nextSafeZone->getWorldPosition(), getWorldPosition() + offset);
    }
    if (distanceToSafe < step * step) {
        if (addAnimalAnimation(nextSafeZone, mDuration)) {
            changeDirection(direction);
        }
    }
    else {
        if (nextUnsafeZone == nullptr) {
            return;
        }
        if (addAnimalAnimation(nextUnsafeZone, mDuration)) {
            changeDirection(direction);
        }
    }
    // if (addStaticAnimation(offset, duration)) {
    //     changeDirection(direction);
    // }

}