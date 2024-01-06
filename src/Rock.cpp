#include "Rock.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Textures::ID toTextureID(Rock::Type type)
{
    //No general return
	switch (type)
	{
	case Rock::Rock1:
        return Textures::Rock1;
	}
}

Rock::Rock(Type type, const TextureHolder& textures): 
    mType(type)
    ,mSprite(textures.get(toTextureID(type)))
{
    setSize(mSprite, sf::Vector2f(50, 50));
    centerOrigin(mSprite);
}

void Rock::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
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

sf::FloatRect Rock::getHitbox() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int Rock::getCategory() const
{
    //No general return
    switch (mType)
    {
    case Rock1:
        return Category::Obstacle | Category::HardObstacle;
    }
}

