#pragma once

#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class WalkingAnimal: public Entity
{
public:
    enum Type {
        Pig,
        Lion,
        Fox, 
    };
public:
                            WalkingAnimal(Type type, sf::Vector2f position, const TextureHolder& textures, Road* road);
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;
    void                    ChangeState(int x);

private:
    
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
		sf::Sprite				            mSprite[4];
        int                                 HEIGHT_SIZE = 35;
        int                                 WIDTH_SIZE = 30;
        const TextureHolder&                textures;
        int                                 curChoose;      
};