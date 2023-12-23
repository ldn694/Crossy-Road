#pragma once

#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class FloatingLog: public Entity
{
public:
    enum Type{
        Lily,
        SmallLog,
        BigLog,
        NumTypes
    };
                            FloatingLog(Type type, sf::Vector2f position, const TextureHolder& textures, Road* road);
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;
    std::vector <Zone*>     getZones() const;


	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
        Type					            mType;
		sf::Sprite				            mSprite;
        std::vector <Zone*>                 mZones;
};