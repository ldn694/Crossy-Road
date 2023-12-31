#pragma once
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.hpp"
#include "Choice.hpp"
#include "TypeBox.hpp"
#include "ClickableList.hpp"


class GameStartState : public State
{
public:
	GameStartState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

	void					loadTextures(Context context);


private:
	enum ButtonNames
	{
		Play,
		OnePlayer,
		TwoPlayer,
		Easy,
		Medium,
		Hard,
		Extreme,
		Back,
		LeftArrow,
		RightArrow,
		TypingBox,
		TypingBox2P_First,
		TypingBox2P_Second,
		LeftArrow2P_First,
		RightArrow2P_First,
		LeftArrow2P_Second,
		RightArrow2P_Second,
	};


private:
	sf::Sprite				mCharacterSprite;
	ClickableList			mClickableList;
	std::vector<sf::Text>	mTexts;
	std::size_t				mChoicePlayerIndex, mChoiceDifficultyIndex, mCharacterIndex1P, mCharacterIndex2P_First, mCharacterIndex2P_Second;
	std::size_t 			mCharacterCount = 5;
	Textures::ID			mCharacterList[10];
	sf::Sprite				mCharacterListSprite[10], mCharacterListSprite2P_First[10], mCharacterListSprite2P_Second[10];
	sf::RectangleShape		mBackground;
};
