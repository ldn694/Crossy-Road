#include "StopLight.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


StopLight::StopLight(sf::Vector2f position, const TextureHolder& textures, Road* road)
{
    float width, height;
    width = WIDTH_SIZE;
    height = HEIGHT_SIZE;
    mSprite[Red].setTexture(textures.get(Textures::StopLightRed));
    mSprite[Yellow].setTexture(textures.get(Textures::StopLightYellow));
    mSprite[Green].setTexture(textures.get(Textures::StopLightGreen));
    for (int i = 0; i < NumStopLightState; i++) {  
        State state = static_cast<State>(i);
        setSize(mSprite[state], sf::Vector2f(width, height));
    }
    setOrigin(sf::Vector2f(width / 2, height));
    setDefaultState();
}

void StopLight::setDefaultState() {
    curState = Green;
}

StopLight::State StopLight::getState() const {
    return curState;
}

void StopLight::changeState() {
    switch (curState) {
    case Red:
        curState = Green;
        break;
    case Yellow:
        curState = Red;
        break;
    case Green:
        curState = Yellow;
        break;
    default:
        break;
    }
}

void StopLight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite.at(curState), states);
    // target.draw(mSprite[curState], states);
}

unsigned int StopLight::getCategory() const
{
    return Category::None;
}

