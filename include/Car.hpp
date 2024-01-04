#pragma once

#include "Zone.hpp"
#include "SoundPlayer.hpp"
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
        TruckLeft,
        TruckRight,
        VanLeft,
        VanRight,
        NumTypes
    };
                            Car(Type type, sf::Vector2f position, const TextureHolder& textures, SoundPlayer& sounds, Road* road);
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;


	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void            updateCurrent(sf::Time dt);


private:
        SoundPlayer&                        mSounds;
        Type					            mType;
		sf::Sprite				            mSprite;
        std::vector <Zone*>                 mZones;
        int                                 HEIGHT_SIZE = 60;
        int                                 WIDTH_SIZE = 80;
        sf::Time                            mTimeSinceLastHonk;
        const sf::Time                      mHonkPeriod = sf::seconds(20.0f);
};