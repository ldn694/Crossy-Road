#pragma once

#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Car: public Entity
{
public:
    enum Type{
        RedCarLeft,
        BlueCarLeft,
        RedCarRight,
        BlueCarRight,
        NumTypes
    };
                            Car(Type type, sf::Vector2f position, const TextureHolder& textures, Road* road);
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;


	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
        Type					            mType;
		sf::Sprite				            mSprite;
        std::vector <Zone*>                 mZones;
        int                                 HEIGHT_SIZE = 60;
        int                                 WIDTH_SIZE = 80;
};