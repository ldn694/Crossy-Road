#include "TrafficLight.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


TrafficLight::TrafficLight(sf::Vector2f position, const TextureHolder& textures, Road* road):
    mSprite(textures.get(Textures::TrafficLight)),
    textures(textures)
{
    float width, height;
    width = WIDTH_SIZE;
    height = HEIGHT_SIZE;
    setSize(mSprite, sf::Vector2f(width, height));
    mSprite.setPosition(-12, 0);
}
void TrafficLight::setDefaultColor(){
    mSprite.setTexture(textures.get(Textures::TrafficLight));
}
void TrafficLight::changeColor(){
    if (Left) mSprite.setTexture(textures.get(Textures::TrafficLight1));
    else mSprite.setTexture(textures.get(Textures::TrafficLight2));
    Left = !Left;

}

void TrafficLight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
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

sf::FloatRect TrafficLight::getHitbox() const
{
    return getWorldTransform().transformRect(sf::FloatRect(-25, -5, WIDTH_SIZE * 0.96, HEIGHT_SIZE * 0.9));
}

unsigned int TrafficLight::getCategory() const
{
    return Category::None;
}

