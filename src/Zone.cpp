#include "Zone.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "River.hpp"
#include "Land.hpp"

Zone::Zone(Zone::Safety safety, sf::FloatRect hitbox, Road* road):
    mRoad(road)
{
    setPosition(hitbox.left + hitbox.width / 2, hitbox.top + hitbox.height / 2);
    mHitbox = sf::FloatRect(-hitbox.width / 2, -hitbox.height / 2, hitbox.width, hitbox.height);
    mSafety = safety;
}

Zone::~Zone() {
    // if (dynamic_cast<River*>(mRoad) != nullptr) {
    //     std::cerr << "River zone deleted\n";
    // }
    // if (dynamic_cast<Land*>(mRoad) != nullptr) {
    //     std::cerr << "Land zone deleted\n";
    // }
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
    // sf::FloatRect rect = mHitbox;
    // sf::RectangleShape hitbox = sf::RectangleShape();
    // hitbox.setSize(sf::Vector2f(rect.width, rect.height));
    // hitbox.setFillColor(sf::Color::Transparent);
    // hitbox.setOutlineColor(sf::Color::Green);
    // hitbox.setOutlineThickness(1);
    // hitbox.setPosition(rect.left, rect.top);
    // target.draw(hitbox, states);
}

unsigned int Zone::getCategory() const
{
    //No general return
    switch(mSafety) {
        case Safe:
            return Category::SafeZone;
        case Unsafe:
            return Category::DeadZone;
    }
}

Road* Zone::getRoad() const
{
    return mRoad;
}
