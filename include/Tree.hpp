#pragma once

#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Tree: public Entity
{
public:
    enum Type{
        SmallTree,
        MediumTree,
        BigTree,
        NumTypes
    };
                            Tree(Type type, const TextureHolder& textures);
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;


	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
        Type					            mType;
		sf::Sprite				            mSprite;
};