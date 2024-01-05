#include "Car.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Textures::ID toTextureID(Car::Type type)
{
    //No general return
    switch (type)
    {
    case Car::RedCarLeft:
        return Textures::RedCarLeft;
    case Car::RedCarRight:
        return Textures::RedCarRight;
    case Car::BlueCarLeft:
        return Textures::BlueCarLeft;
    case Car::BlueCarRight:
        return Textures::BlueCarRight;
    case Car::TruckLeft:
        return Textures::TruckLeft;
    case Car::TruckRight:
        return Textures::TruckRight;
    case Car::VanLeft:
        return Textures::VanLeft;
    case Car::VanRight:
        return Textures::VanRight;
    }
}

Car::Car(Type type, sf::Vector2f position, const TextureHolder& textures, SoundPlayer& sounds, Road* road):
    mType(type)
    ,mSprite(textures.get(toTextureID(type)))
    ,mSounds(sounds)
{
    float width, height;
    width = WIDTH_SIZE;
    height = HEIGHT_SIZE;
    setSize(mSprite, sf::Vector2f(width, height));
    centerOrigin(mSprite);
    mSprite.setPosition(15, 18);
    mTimeSinceLastHonk = sf::seconds(rand() % 20);
}

void Car::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
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

void Car::updateCurrent(sf::Time dt)
{
    Entity::updateCurrent(dt);
    //honk
    mTimeSinceLastHonk += dt;
    if (mTimeSinceLastHonk >= mHonkPeriod) {
        sf::Sound& honk = mSounds.play(SoundEffect::Car_Honk, getWorldPosition(), 0.1f);
        honk.setAttenuation(50.f);
        mTimeSinceLastHonk = sf::Time::Zero;
    }
}

sf::FloatRect Car::getHitbox() const
{
    return getWorldTransform().transformRect(sf::FloatRect(-25, -5, WIDTH_SIZE * 0.9, HEIGHT_SIZE * 0.9));
}

unsigned int Car::getCategory() const
{
    return Category::Hostile;
}

