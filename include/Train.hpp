#pragma once

#include "SoundPlayer.hpp"
#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Train: public Entity
{
public:
                            Train(sf::Vector2f position, SoundPlayer& sounds, const TextureHolder& textures, Road* road);
                            ~Train();
    virtual unsigned int	getCategory() const;
    sf::FloatRect			getHitbox() const;


	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void            updateCurrent(sf::Time dt);


private:
        sf::Sound&                          mSound;
        SoundPlayer&                        sounds;
		sf::Sprite				            mSprite;
        int                                 HEIGHT_SIZE = 60;
        int                                 WIDTH_SIZE = 1050 + 200;
        sf::Time                            mTimeSinceLastUpdate;
        const sf::Time                      FULL_VOLUME_TIME = sf::seconds(0.5f);
        const sf::Time                      FADE_OUT_TIME = sf::seconds(0.3f);
};