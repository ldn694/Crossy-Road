#include "Aircraft.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Eagle:
		return Textures::Eagle;

	case Aircraft::AllyRaptor:
		return Textures::Raptor;

	case Aircraft::EnemyRaptor:
		return Textures::Raptor;
	}
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
	: mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	centerOrigin(mSprite);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
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

sf::FloatRect Aircraft::getHitbox() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Eagle:
		return Category::Player;

	case AllyRaptor:
		return Category::AlliedAircraft | Category::Obstacle;

	default:
		return Category::EnemyAircraft | Category::Hostile;
	}
}
