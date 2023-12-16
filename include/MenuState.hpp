#pragma once
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.hpp"
#include "Choice.hpp"
#include "ClickableList.hpp"


class MenuState : public State
{
public:
	MenuState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

	void					updateOptionText();


	private:
		enum OptionNames
		{
			Play,
			Exit,
			Setting,
		};


private:
	sf::Sprite				mBackgroundSprite;
	ClickableList			mClickableList;
	std::vector<sf::Text>	mOptions;
	std::size_t				mOptionIndex;
	std::size_t				mChoiceIndex;

};
