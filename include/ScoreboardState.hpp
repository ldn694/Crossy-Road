#pragma once
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.hpp"
#include "Choice.hpp"
#include "ClickableList.hpp"


class ScoreboardState : public State
{
public:
	ScoreboardState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

	void					updateOptionText();
		enum ClickableID {
			ID1, ID2, ID3, ID4, ID5, 
			quit, mode,left, right,
			name1, score1, 
			name2, score2,
			name3, score3,
			name4, score4,
			name5, score5,
		};


	private:
		enum OptionNames
		{
			
		};


private:
	sf::Sprite				mBackgroundSprite;
	ClickableList			mClickableList;
	std::vector<sf::Text>	mOptions;
	std::size_t				mOptionIndex;
	std::size_t				mChoiceIndex;

};