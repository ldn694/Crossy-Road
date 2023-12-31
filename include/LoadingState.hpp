#pragma once

#include "State.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>



class LoadingState : public State
{
public:
	LoadingState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);


private:
	sf::Text				mLoadingText;
	sf::Clock				mClock;
	sf::String				mString;
	int 				    mCount;
	sf::Sprite				mBackgroundSprite;

};
