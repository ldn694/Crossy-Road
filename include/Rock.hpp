#pragma once

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Rock: public Entity 
{
public:
    enum Type{
        Rock1,
        NumTypes
    };
                            Rock(Type type, const TextureHolder& textures);
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;


	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
		Type					mType;
		sf::Sprite				mSprite;
};