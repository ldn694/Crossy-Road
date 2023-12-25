#pragma once

#include "Zone.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class StopLight: public SceneNode
{
public:
    enum State {
        Red,
        Yellow,
        Green,
        NumStopLightState
    };
                            StopLight(sf::Vector2f position, const TextureHolder& textures, Road* road);
    virtual unsigned int	getCategory() const;
    void                    changeState();
    void                    setDefaultState();
    State                   getState() const;

    
	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
		std::map <State, sf::Sprite>        mSprite;
        int                                 HEIGHT_SIZE = 50;
        int                                 WIDTH_SIZE = 25;
        State                               curState;
};