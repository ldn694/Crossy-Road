#include "Aircraft.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


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
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Eagle:
		return Category::PlayerAircraft;

	case AllyRaptor:
		return Category::AlliedAircraft;

	default:
		return Category::EnemyAircraft;
	}
}
