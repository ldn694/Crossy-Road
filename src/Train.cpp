#include "Train.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


Train::Train(sf::Vector2f position, SoundPlayer& sounds, const TextureHolder& textures, Road* road):
    mSprite(textures.get(Textures::Train)),
    mSound(sounds.play(SoundEffect::Train_Passing, getWorldPosition()))
{
    mSound.setMinDistance(1.f);
    float width, height;
    width = WIDTH_SIZE;
    height = HEIGHT_SIZE;
    setSize(mSprite, sf::Vector2f(width, height));
    mSprite.setPosition(-12, 0);
}

Train::~Train()
{
    mSound.stop();
}

void Train::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
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

void Train::updateCurrent(sf::Time dt)
{
    Entity::updateCurrent(dt);
    mSound.setPosition(sf::Vector3f(getWorldPosition().x, getWorldPosition().y, 0));
}

sf::FloatRect Train::getHitbox() const
{
    return getWorldTransform().transformRect(sf::FloatRect(-25, -5, WIDTH_SIZE * 0.96, HEIGHT_SIZE * 0.9));
}

unsigned int Train::getCategory() const
{
    return Category::Hostile;
}

