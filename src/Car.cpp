#include "Car.hpp"
#include "ResourceHolder.hpp"
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
    }
}

Car::Car(Type type, sf::Vector2f position, const TextureHolder& textures, Road* road):
    mType(type)
    ,mSprite(textures.get(toTextureID(type)))
{
    float width, height;
    width = WIDTH_SIZE;
    height = HEIGHT_SIZE;
    setSize(mSprite, sf::Vector2f(width, height));
    centerOrigin(mSprite);
    mSprite.setPosition(15, 18);
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

sf::FloatRect Car::getHitbox() const
{
    return getWorldTransform().transformRect(sf::FloatRect(-25, -5, WIDTH_SIZE * 0.9, HEIGHT_SIZE * 0.9));
}

unsigned int Car::getCategory() const
{
    return Category::Hostile;
}
