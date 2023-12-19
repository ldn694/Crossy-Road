#include "Zone.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Zone::Zone(Zone::Safety safety, sf::FloatRect hitbox)
{
    mHitbox = hitbox;
    mSafety = safety;
}

sf::FloatRect Zone::getHitbox() const
{
    return getWorldTransform().transformRect(mHitbox);
}

Zone::Safety Zone::getSafety() const
{
    return mSafety;
}

void Zone::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //draw hitbox
    sf::RectangleShape hitbox;
    hitbox.setSize(sf::Vector2f(mHitbox.width, mHitbox.height));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1);
    hitbox.setPosition(mHitbox.left, mHitbox.top);
    target.draw(hitbox, states);
}
