#include "Animal.hpp"
#include "Category.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Animal::Animal(Type type, TextureHolder& textures) : mType(type), mTextures(textures)
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

Textures::ID Animal::toTextureID(Type type, Direction direction) {
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

void Animal::changeDirection(Direction direction)
{
    mDirection = direction;
    mSprite.setTexture(mTextures.get(toTextureID(mType, direction)));
    mSprite.setScale(0.2, 0.2);
    centerOrigin(mSprite);
}

void Animal::move(Direction direction)
{
    float step = 70.f;
    sf::Time duration = sf::seconds(0.5f);
    sf::Vector2f offset;
    switch (direction) {
        case Animal::Direction::Left:
            offset = sf::Vector2f(-step, 0.f);
            break;
        case Animal::Direction::Right:
            offset = sf::Vector2f(step, 0.f);
            break;
        case Animal::Direction::Up:
            offset = sf::Vector2f(0.f, -step);
            break;
        case Animal::Direction::Down:
            offset = sf::Vector2f(0.f, step);
            break;
        default:
            break;
    }
    if (addStaticAnimation(offset, duration)) {
        changeDirection(direction);
    }
}