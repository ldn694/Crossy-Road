#pragma once

#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class TrafficLight: public Entity
{
public:
                            TrafficLight(sf::Vector2f position, const TextureHolder& textures, Road* road);
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;

    void                    changeColor();
    void                    setDefaultColor();
	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
		sf::Sprite				            mSprite[3];
        int                                 HEIGHT_SIZE = 50;
        int                                 WIDTH_SIZE = 45;
        const TextureHolder&                textures;
        int                                 curChoose;      
};