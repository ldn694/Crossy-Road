#pragma once

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Button.hpp"
#include "ClickableList.hpp"


class PauseState : public State
{
public:
	enum ButtonNames
	{
		Home,
		Resume,
		Setting,
	};

	PauseState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);
	void 				loadTextures(Context mContext);


private:
	sf::Sprite						mBackgroundSprite;
	std::vector<sf::Text>			mPausedText;
	ClickableList					mClickableList;
};