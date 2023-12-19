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
    loadTextures(context);

	sf::Font& font = context.fonts->get(Fonts::Main);
	mBackground.setPosition(0, 0);
	mBackground.setSize(sf::Vector2f(context.window->getView().getSize().x, context.window->getView().getSize().y));
	mBackground.setFillColor(sf::Color(196,199,215));
	

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
	info.floatList = { 10, 10, 100, 100, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Quit, Textures::QuitHovered };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Back, info);

    //Play button
	info.floatList = { 1080 - 150, 600 - 100, 75, 75, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Next, Textures::NextHovered };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Play, info);

	//Right arrow button
	info.floatList = { 300, 300, 50, 50, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::SelectRight, Textures::SelectRightHovered };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::RightArrow, info);

	//Left arrow button
	info.floatList = { 200, 300, 50, 50, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::SelectLeft, Textures::SelectLeftHovered };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::LeftArrow, info);

    //Choice setting
	mClickableList.registerClickable<Choice>(Clickable::Type::Choice);
    //Difficulty choice
    for (int i=0; i < 3; i++){
        std::size_t idOfButton;
        switch (i){
            case 0:
                idOfButton = ButtonNames::Easy;
				info.textureIDList = { Textures::EasyChoice, Textures::EasyHoveredChoice, Textures::EasyPressedChoice };
                break;
            case 1:
                idOfButton = ButtonNames::Medium;
				info.textureIDList = { Textures::MediumChoice, Textures::MediumHoveredChoice, Textures::MediumPressedChoice };
                break;
            case 2:
                idOfButton = ButtonNames::Hard;
				info.textureIDList = { Textures::HardChoice, Textures::HardHoveredChoice, Textures::HardPressedChoice };
                break;
        }
        info.floatList = { 1080 - 380, 140.f + 110.f * i, 225, 90, 10 };
        info.stringList = { "" };
        info.status = Clickable::Status(true, true, true);
        info.fontIDList = { Fonts::Main };
        info.colorList = { sf::Color::White };
        mClickableList.addClickable(Clickable::Type::Choice, idOfButton, info);
    }
	mChoiceDifficultyIndex = ButtonNames::Easy;
	mClickableList.setClickable(mChoiceDifficultyIndex, false);

    //Choice of character
    for (int i=0; i < 2; i++){
        std::size_t idOfButton;
        switch (i){
            case 0:
                idOfButton = ButtonNames::OnePlayer;
				info.textureIDList = { Textures::OnePlayerChoice, Textures::OnePlayerHoveredChoice, Textures::OnePlayerPressedChoice };
                break;
            case 1:
                idOfButton = ButtonNames::TwoPlayer;
				info.textureIDList = { Textures::TwoPlayer, Textures::TwoPlayerHoveredChoice, Textures::TwoPlayerPressedChoice };
                break;
        }
        info.floatList = { 1080 - 380 + 114.f * i, 5, 113, 113, 20 };
        info.stringList = { "" };
        info.status = Clickable::Status(true, true, true);
        info.fontIDList = { Fonts::Main };
        
        info.colorList = { sf::Color::White };
        mClickableList.addClickable(Clickable::Type::Choice, idOfButton, info);
    }
    mChoicePlayerIndex = ButtonNames::OnePlayer;
    mClickableList.setClickable(mChoicePlayerIndex, false);
}

void GameStartState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackground);
	/*FOREACH(const sf::Text & text, mTexts)
		window.draw(text);*/
	mClickableList.draw();
}
void GameStartState::loadTextures(Context context){
	context.textures->load(Textures::GameStartBackground, "Assets/Images/ForSetupGameStart/background/GameStartBackground.png");
    context.textures->load(Textures::EasyChoice, "Assets/Images/ForSetupGameStart/mode/easy.png");
	context.textures->load(Textures::EasyPressedChoice, "Assets/Images/ForSetupGameStart/mode/easy_selected.png");
	context.textures->load(Textures::EasyHoveredChoice, "Assets/Images/ForSetupGameStart/mode/easy_hover.png");
	context.textures->load(Textures::MediumChoice, "Assets/Images/ForSetupGameStart/mode/medium.png");
	context.textures->load(Textures::MediumPressedChoice, "Assets/Images/ForSetupGameStart/mode/medium_selected.png");
	context.textures->load(Textures::MediumHoveredChoice, "Assets/Images/ForSetupGameStart/mode/medium_hover.png");
	context.textures->load(Textures::HardChoice, "Assets/Images/ForSetupGameStart/mode/hard.png");
	context.textures->load(Textures::HardPressedChoice, "Assets/Images/ForSetupGameStart/mode/hard_selected.png");
	context.textures->load(Textures::HardHoveredChoice, "Assets/Images/ForSetupGameStart/mode/hard_hover.png");
	context.textures->load(Textures::OnePlayerChoice, "Assets/Images/ForSetupGameStart/player/1P.png");
	context.textures->load(Textures::OnePlayerPressedChoice, "Assets/Images/ForSetupGameStart/player/1P_click.png");
	context.textures->load(Textures::OnePlayerHoveredChoice, "Assets/Images/ForSetupGameStart/player/1P_hover.png");
	context.textures->load(Textures::TwoPlayer, "Assets/Images/ForSetupGameStart/player/2P.png");
	context.textures->load(Textures::TwoPlayerPressedChoice, "Assets/Images/ForSetupGameStart/player/2P_click.png");
	context.textures->load(Textures::TwoPlayerHoveredChoice, "Assets/Images/ForSetupGameStart/player/2P_hover.png");
	context.textures->load(Textures::Quit, "Assets/Images/ForSetupGameStart/quit/quit.png");
	context.textures->load(Textures::QuitHovered, "Assets/Images/ForSetupGameStart/quit/quit_hover.png");
	context.textures->load(Textures::Next, "Assets/Images/ForSetupGameStart/next/next.png");
	context.textures->load(Textures::NextHovered, "Assets/Images/ForSetupGameStart/next/next_hover.png");
	context.textures->load(Textures::SelectLeft, "Assets/Images/ForSetupGameStart/select/select_left.png");
	context.textures->load(Textures::SelectLeftHovered, "Assets/Images/ForSetupGameStart/select/select_left_hover.png");
	context.textures->load(Textures::SelectRight, "Assets/Images/ForSetupGameStart/select/select_right.png");
	context.textures->load(Textures::SelectRightHovered, "Assets/Images/ForSetupGameStart/select/select_right_hover.png");

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
                requestStackPush(States::Game, info);
            } else if (announcement.id == ButtonNames::Back){
                requestStackPop();
                State::Info info;
                requestStackPush(States::Menu, info);
            } else if (announcement.id == ButtonNames::OnePlayer || announcement.id == ButtonNames::TwoPlayer){
                mClickableList.setClickable(mChoicePlayerIndex, true);
                mClickableList.setClickable(announcement.id, false);
                mChoicePlayerIndex = announcement.id;
            } else if (announcement.id == ButtonNames::LeftArrow || announcement.id == ButtonNames::RightArrow){
				
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


	return true;
}
