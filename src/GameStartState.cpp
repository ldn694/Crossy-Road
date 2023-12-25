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
	

	/*//Title
	sf::Text TitleText;
	TitleText.setFont(font);
	TitleText.setString("CROSSING ROAD");
    TitleText.setCharacterSize(50);
	centerOrigin(TitleText);
	TitleText.setPosition(context.window->getView().getSize().x / 2.f, 50.f);
    
	mTexts.push_back(TitleText);*/

	//Character
	mCharacterList[0] = Textures::Cat;
	mCharacterList[1] = Textures::Chicken;
	mCharacterList[2] = Textures::Fox;
	mCharacterList[3] = Textures::Lion;
	mCharacterList[4] = Textures::Pig;

	mCharacterIndex = 0;
	for (int i=0; i<mCharacterCount; i++){
		mCharacterListSprite[i].setTexture(context.textures->get(mCharacterList[i]));
		setSize(mCharacterListSprite[i], sf::Vector2f(330, 330));
		mCharacterListSprite[i].setPosition(194, 135);
	}

    
    //Button Setting
	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;

    //Back button
	info.floatList = { 50, 20, 65, 65, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Quit, Textures::QuitHovered };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Back, info);

    //Play button
	info.floatList = { 1080 - 150, 600 - 90, 65, 65, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Next, Textures::NextHovered };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Play, info);

	//Right arrow button
	info.floatList = { 500, 280, 50, 50, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::SelectRight, Textures::SelectRightHovered };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::RightArrow, info);

	//Left arrow button
	info.floatList = { 150, 280, 50, 50, 10 };
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
        info.floatList = { 1080 - 380, 175.f + 120.f * i, 200, 95, 10 };
        info.stringList = { "" };
        info.status = Clickable::Status(true, true, true);
        info.fontIDList = { Fonts::Main };
        info.colorList = { sf::Color::White };
        mClickableList.addClickable(Clickable::Type::Choice, idOfButton, info);
    }
	mChoiceDifficultyIndex = ButtonNames::Easy;
	mClickableList.setClickable(mChoiceDifficultyIndex, false);

    //Choice of num player
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
        info.floatList = { 1080 - 390 + 114.f * i, 30, 110, 110, 20 };
        info.stringList = { "" };
        info.status = Clickable::Status(true, true, true);
        info.fontIDList = { Fonts::Main };
        
        info.colorList = { sf::Color::White };
        mClickableList.addClickable(Clickable::Type::Choice, idOfButton, info);
    }
    mChoicePlayerIndex = ButtonNames::OnePlayer;
    mClickableList.setClickable(mChoicePlayerIndex, false);

	//TypeBox setting
	mClickableList.registerClickable<TypeBox>(Clickable::Type::TypeBox);
	info.floatList = { 190, 465, 350, 100, 1.0/6, 50, 30 };
	info.stringList = { "Player" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Bungee, Fonts::Bungee };
	info.textureIDList = { Textures::TypeBox, Textures::TypeBoxHovered, Textures::TypeBoxInput };	
	info.colorList = { sf::Color::Black, sf::Color::White };
	mClickableList.addClickable(Clickable::Type::TypeBox, ButtonNames::TypingBox, info);
}

void GameStartState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackground);
	/*FOREACH(const sf::Text & text, mTexts)
		window.draw(text);*/
	window.draw(mCharacterListSprite[mCharacterIndex]);
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

	context.textures->load(Textures::Cat, "Assets/Images/ForSetupGameStart/character/cat.png");
	context.textures->load(Textures::Chicken, "Assets/Images/ForSetupGameStart/character/chicken.png");
	context.textures->load(Textures::Fox, "Assets/Images/ForSetupGameStart/character/fox.png");
	context.textures->load(Textures::Lion, "Assets/Images/ForSetupGameStart/character/lion.png");
	context.textures->load(Textures::Pig, "Assets/Images/ForSetupGameStart/character/pig.png");

	context.textures->load(Textures::TypeBox, "Assets/Images/ForSetupGameStart/other_button/normal.png");
	context.textures->load(Textures::TypeBoxHovered, "Assets/Images/ForSetupGameStart/other_button/hover.png");
	context.textures->load(Textures::TypeBoxInput, "Assets/Images/ForSetupGameStart/other_button/selected.png");
}
bool GameStartState::update(sf::Time dt)
{
	mClickableList.update(dt);
	return false;
}

bool GameStartState::handleEvent(const sf::Event& event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			std::cerr << "Left Clicked " << announcement.id << "\n";
            if (announcement.id == ButtonNames::Play){
                // requestStateClear();
                State::Info info;
				info.stringList.push_back(mClickableList.getString(ButtonNames::TypingBox));
				switch (mChoiceDifficultyIndex)
				{
				case ButtonNames::Easy:
					info.stringList.push_back("Easy");
					break;
				case ButtonNames::Medium:
					info.stringList.push_back("Medium");
					break;
				case ButtonNames::Hard:
					info.stringList.push_back("Hard");
					break;
				default:
					break;
				}
				switch (mChoicePlayerIndex)
				{
				case ButtonNames::OnePlayer:
					info.floatList.push_back(1);
					break;
				case ButtonNames::TwoPlayer:
					info.floatList.push_back(2);
					break;
				default:
					break;
				}
				switch (mCharacterIndex)
				{
				case 0:
					info.stringList.push_back("Cat");
					break;
				case 1:
					info.stringList.push_back("Chicken");
					break;
				case 2:
					info.stringList.push_back("Fox");
					break;
				case 3:
					info.stringList.push_back("Lion");
					break;
				case 4:
					info.stringList.push_back("Pig");
					break;
				default:
					break;
				}
				for (int i = 0; i < info.stringList.size(); i++) {
					std::cout << info.stringList[i] << "\n";
				}
				std::cout << info.floatList[0] << "\n";
                requestStackPush(States::Game, info);
				requestStackPush(States::Loading);
            } else if (announcement.id == ButtonNames::Back){
                requestStackPop();
                State::Info info;
                requestStackPush(States::Menu, info);
            } else if (announcement.id == ButtonNames::OnePlayer || announcement.id == ButtonNames::TwoPlayer){
                mClickableList.setClickable(mChoicePlayerIndex, true);
                mClickableList.setClickable(announcement.id, false);
                mChoicePlayerIndex = announcement.id;
            } else if (announcement.id == ButtonNames::LeftArrow){
				if (mCharacterIndex == 0){
					mCharacterIndex = mCharacterCount - 1;
				} else {
					mCharacterIndex--;
				}
			} else if ( announcement.id == ButtonNames::RightArrow){
				if (mCharacterIndex == mCharacterCount - 1){
					mCharacterIndex = 0;
				} else {
					mCharacterIndex++;
				}
			} else if (announcement.id == ButtonNames::TypingBox){
				mClickableList.setClickable(announcement.id, false);
			} else {
				mClickableList.setClickable(mChoiceDifficultyIndex, true);
				mClickableList.setClickable(announcement.id, false);
				mChoiceDifficultyIndex = announcement.id;
			}
		}
		else if (announcement.action == Clickable::RightPressed) {
			std::cerr << "Right Clicked " << announcement.id << "\n";
		}
	}
	while (pendingNotification()) {
		State::Info info = popNotification();
		std::cerr << info.stringList[0] << "\n";
	}
	if (event.type == sf::Event::MouseButtonPressed) {

	}
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;


	return false;
}
