#include "Tree.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Textures::ID toTextureID(Tree::Type type)
{
    //No general return
    switch (type)
    {
    case Tree::SmallTree:
        return Textures::SmallTree;
    case Tree::MediumTree:
        return Textures::MediumTree;
    case Tree::BigTree:
        return Textures::BigTree;
    }
}

Tree::Tree(Type type, const TextureHolder& textures) :
    mType(type)
    , mSprite(textures.get(toTextureID(type)))
{
    float width, height;
    switch (type) {
    case SmallTree:
        width = 70;
        height = 60;
        break;
    case MediumTree:
        width = 80;
        height = 100;
        break;
    case BigTree:
        width = 90;
        height = 120;
        break;
    }
    setSize(mSprite, sf::Vector2f(width, height));
    mSprite.setOrigin(0, mSprite.getGlobalBounds().height);
    mSprite.setPosition(-35, -32.5);
}

void Tree::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
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

sf::FloatRect Tree::getHitbox() const
{
    sf::FloatRect rect;
    switch (mType) {
    case SmallTree:
        rect = sf::FloatRect(-20, -25, 20, 10);
        break;
    case MediumTree:
        rect = sf::FloatRect(-20, -15, 20, 20);
        break;
    case BigTree:
        rect = sf::FloatRect(-15, -15, 20, 20);
        break;
    }

    return getWorldTransform().transformRect(rect);
}

unsigned int Tree::getCategory() const
{
    return Category::Obstacle;
}

