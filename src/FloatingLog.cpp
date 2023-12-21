#include "FloatingLog.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Textures::ID toTextureID(FloatingLog::Type type)
{
    //No general return
	switch (type)
	{
    case FloatingLog::Lily:
        return Textures::Lily;
    case FloatingLog::SmallLog:
        return Textures::SmallLog;
    case FloatingLog::BigLog:
        return Textures::BigLog;
	}
}

FloatingLog::FloatingLog(Type type, sf::Vector2f position, const TextureHolder& textures, Road* road):
    mType(type)
    ,mSprite(textures.get(toTextureID(type)))
{
    float width;
    switch (type) {
        case Lily:
            width = 50;
            break;
        case SmallLog:
            width = 100;
            break;
        case BigLog:
            width = 150;
            break;
    }
    float height = 49;
    setSize(mSprite, sf::Vector2f(width, height));
    int numZones;
    switch (type) {
        case Lily:
            numZones = 1;
            break;
        case SmallLog:
            numZones = 2;
            break;
        case BigLog:
            numZones = 3;
            break;
    }
    float zoneWidth = width / numZones;
    float zoneHeight = height;
    for (int i = 0; i < numZones; i++) {
        sf::Vector2f zonePosition(i * zoneWidth, 0);
        std::unique_ptr<Zone> zone(new Zone(Zone::Safety::Safe, sf::FloatRect(zonePosition, sf::Vector2f(zoneWidth, zoneHeight)), road));
        mZones.push_back(zone.get());
        requestAttach(std::move(zone));
    }
}

void FloatingLog::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
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

sf::FloatRect FloatingLog::getHitbox() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int FloatingLog::getCategory() const
{
    return Category::None;
}

std::vector <Zone*> FloatingLog::getZones() const
{
    return mZones;
}

