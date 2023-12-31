#pragma once

#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Train: public Entity
{
public:
                            Train(sf::Vector2f position, const TextureHolder& textures, Road* road);
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;


	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
		sf::Sprite				            mSprite;
        int                                 HEIGHT_SIZE = 60;
        int                                 WIDTH_SIZE = 1050 + 200;
};