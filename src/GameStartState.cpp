#include "GameStartState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <string>

GameStartState::GameStartState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context), mTexts(), mClickableList(context)
{   
    context.textures->load(Textures::GameStartBackground, "Assets/Images/GameStartBackground.png");
    context.textures->load(Textures::Choice, "Assets/Images/Choice.png");
	context.textures->load(Textures::PressedChoice, "Assets/Images/Button.png");
	context.textures->load(Textures::HoveredChoice, "Assets/Images/HoveredChoice.png");
	context.textures->load(Textures::Button, "Assets/Images/Button.png");
	context.textures->load(Textures::PressedButton, "Assets/Images/PressedButton.png");
	context.textures->load(Textures::LeftArrowButton, "Assets/Images/LeftArrowButton.png");
	context.textures->load(Textures::LeftHoveredArrowButton, "Assets/Images/LeftHoveredArrowButton.png");
	context.textures->load(Textures::RightArrowButton, "Assets/Images/RightArrowButton.png");
	context.textures->load(Textures::RightHoveredArrowButton, "Assets/Images/RightHoveredArrowButton.png");
	context.textures->load(Textures::TypeBox, "Assets/Images/TypeBox.png");
	context.textures->load(Textures::TypeBoxHovered, "Assets/Images/TypeBoxHovered.png");
	context.textures->load(Textures::TypeBoxInput, "Assets/Images/TypeBoxInput.png");
	sf::Texture& texture = context.textures->get(Textures::GameStartBackground);
	sf::Font& font = context.fonts->get(Fonts::Main);

	mBackgroundSprite.setTexture(texture);

	//Title
	sf::Text TitleText;
	TitleText.setFont(font);
	TitleText.setString("CROSSING ROAD");
    TitleText.setCharacterSize(50);
	centerOrigin(TitleText);
	TitleText.setPosition(context.window->getView().getSize().x / 2.f, 50.f);
    
	mTexts.push_back(TitleText);

    
    //Button Setting
	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;

    //Back button
	info.floatList = { 0, 0, 100, 100, 10 };
	info.stringList = { "Back" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Button, Textures::PressedButton };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Back, info);

    //Play button
	info.floatList = { 510, 380, 100, 100, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Button, Textures::PressedButton };
	info.stringList = { "Play" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Play, info);

	//Right arrow button
	info.floatList = { 300, 300, 50, 50, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::RightArrowButton, Textures::RightHoveredArrowButton };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::RightArrow, info);

	//Left arrow button
	info.floatList = { 200, 300, 50, 50, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::LeftArrowButton, Textures::LeftHoveredArrowButton };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::LeftArrow, info);

    //Choice setting
	mClickableList.registerClickable<Choice>(Clickable::Type::Choice);
    //Difficulty choice
    for (int i=0; i < 4; i++){
        std::string s;
        std::size_t idOfButton;
        switch (i){
            case 0:
                s = "Easy";
                idOfButton = ButtonNames::Easy;
                break;
            case 1:
                s = "Medium";
                idOfButton = ButtonNames::Medium;
                break;
            case 2:
                s = "Hard";
                idOfButton = ButtonNames::Hard;
                break;
            case 3:
                s = "Extreme";
                idOfButton = ButtonNames::Extreme;
                break;
        }
        info.floatList = { 500, 60.f + 80.f * i, 80, 80, 10 };
        info.stringList = { s };
        info.status = Clickable::Status(true, true, true);
        info.fontIDList = { Fonts::Main };
        info.textureIDList = { Textures::Choice, Textures::HoveredChoice, Textures::PressedChoice };
        info.colorList = { sf::Color::White };
        mClickableList.addClickable(Clickable::Type::Choice, idOfButton, info);
    }
	mChoiceDifficultyIndex = ButtonNames::Easy;
	mClickableList.setClickable(mChoiceDifficultyIndex, false);

    //Choice of character
    for (int i=0; i < 2; i++){
        std::string s;
        std::size_t idOfButton;
        switch (i){
            case 0:
                s = "1P";
                idOfButton = ButtonNames::OnePlayer;
                break;
            case 1:
                s = "2P";
                idOfButton = ButtonNames::TwoPlayer;
                break;
        }
        info.floatList = { 540 + 50.f * i, 5, 50, 50, 20 };
        info.stringList = { s };
        info.status = Clickable::Status(true, true, true);
        info.fontIDList = { Fonts::Main };
        info.textureIDList = { Textures::Choice, Textures::HoveredChoice, Textures::PressedChoice };
        info.colorList = { sf::Color::White };
        mClickableList.addClickable(Clickable::Type::Choice, idOfButton, info);
    }
    mChoicePlayerIndex = ButtonNames::OnePlayer;
    mClickableList.setClickable(mChoicePlayerIndex, false);

	//TypeBox setting
	mClickableList.registerClickable<TypeBox>(Clickable::Type::TypeBox);
	info.floatList = { 150, 150, 300, 100, 1.0/6, 50, 30 };
	info.stringList = { "Player" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main, Fonts::Main };
	info.textureIDList = { Textures::TypeBox, Textures::TypeBoxHovered, Textures::TypeBoxInput };	
	info.colorList = { sf::Color::White, sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::TypeBox, ButtonNames::TypingBox, info);

}

void GameStartState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text & text, mTexts)
		window.draw(text);
	mClickableList.draw();
}

bool GameStartState::update(sf::Time dt)
{
	mClickableList.update(dt);
	return true;
}

bool GameStartState::handleEvent(const sf::Event& event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			std::cout << "Left Clicked " << announcement.id << "\n";
            if (announcement.id == ButtonNames::Play){
                requestStackPop();
                State::Info info;
                info.stringList = {"Start from clicking on " + std::to_string(announcement.id) + " button.\n"};
                requestStackPush(States::Game, info);
            } else if (announcement.id == ButtonNames::Back){
                requestStackPop();
                State::Info info;
                info.stringList = {"Back to main from click " + std::to_string(announcement.id) + " button.\n"};
                requestStackPush(States::Menu, info);
            } else if (announcement.id == ButtonNames::OnePlayer || announcement.id == ButtonNames::TwoPlayer){
                mClickableList.setClickable(mChoicePlayerIndex, true);
                mClickableList.setClickable(announcement.id, false);
                mChoicePlayerIndex = announcement.id;
            } else if (announcement.id == ButtonNames::LeftArrow || announcement.id == ButtonNames::RightArrow){
				
			} else if (announcement.id == ButtonNames::TypingBox){
				mClickableList.setClickable(announcement.id, false);
			} else {
				mClickableList.setClickable(mChoiceDifficultyIndex, true);
				mClickableList.setClickable(announcement.id, false);
				mChoiceDifficultyIndex = announcement.id;
			}
		}
		else if (announcement.action == Clickable::RightPressed) {
			std::cout << "Right Clicked " << announcement.id << "\n";
		}
	}
	while (pendingNotification()) {
		State::Info info = popNotification();
		std::cout << info.stringList[0] << "\n";
	}
	if (event.type == sf::Event::MouseButtonPressed) {

	}
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;
	/*if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (mOptionIndex == Exit)
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}

	else if (event.key.code == sf::Keyboard::Up)
	{
		// Decrement and wrap-around
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}

	else if (event.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}*/

	return true;
}
