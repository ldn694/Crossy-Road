#include "TrafficLight.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


TrafficLight::TrafficLight(sf::Vector2f position, const TextureHolder& textures, Road* road):
    textures(textures)
{
    float width, height;
    width = WIDTH_SIZE;
    height = HEIGHT_SIZE;
    mSprite[0].setTexture(textures.get(Textures::TrafficLight));
    mSprite[1].setTexture(textures.get(Textures::TrafficLight1));
    mSprite[2].setTexture(textures.get(Textures::TrafficLight2));
    for (int i=0; i<3; i++){
        setSize(mSprite[i], sf::Vector2f(width, height));
        mSprite[i].setPosition(-12, 0);
    }
    curChoose = 0;
}
void TrafficLight::setDefaultColor(){
    curChoose = 0;
}
void TrafficLight::changeColor(){
    if (curChoose == 0) curChoose=1;
    else if (curChoose == 1) curChoose=2;
    else curChoose=1;
}

void TrafficLight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite[curChoose], states);
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
    return getWorldTransform().transformRect(sf::FloatRect(-25, -5, WIDTH_SIZE, HEIGHT_SIZE));
}

unsigned int TrafficLight::getCategory() const
{
    return Category::None;
}

