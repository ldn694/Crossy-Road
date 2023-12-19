#include "MenuState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>

MenuState::MenuState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context), mOptions(), mOptionIndex(0), mClickableList(context)
{

	sf::Texture &texture = context.textures->get(Textures::M2);
	sf::Font &font = context.fonts->get(Fonts::T2);

	std::string path = "Assets/Images/ForMenu/";

	context.textures->load(Textures::Play, path + "newgame.png");
	context.textures->load(Textures::Play_, path + "newgame_hover.png");
	context.textures->load(Textures::Load, path + "continue.png");
	context.textures->load(Textures::Load_, path + "continue_hover.png");
	context.textures->load(Textures::Score, path + "scoreboard.png");
	context.textures->load(Textures::Score_, path + "scoreboard_hover.png");
	context.textures->load(Textures::Set, path + "setting.png");
	context.textures->load(Textures::Set_, path + "setting_hover.png");
	context.textures->load(Textures::Exit, path + "exit.png");
	context.textures->load(Textures::Exit_, path + "exit_hover.png");

	context.textures->load(Textures::Choice, "Assets/Images/Choice.png");
	context.textures->load(Textures::PressedChoice, "Assets/Images/Button.png");
	context.textures->load(Textures::HoveredChoice, "Assets/Images/HoveredChoice.png");

	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(0.55, 0.55);
	
	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 165, 230, 300, 100, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);          //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::Play, Textures::Play_};	//cac nut
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Play, info);

	info.floatList = {580, 230, 320, 100, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Load, Textures::Load_};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Load, info);

	info.floatList = {160, 320, 320, 100, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Score, Textures::Score_};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Score, info);

	info.floatList = {575, 320, 320, 100, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Set, Textures::Set_};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Set, info);

	info.floatList = {420, 480, 220, 95, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Exit, Textures::Exit_};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Exit, info);

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text & text, mOptions)
		window.draw(text);
	mClickableList.draw();
}

bool MenuState::update(sf::Time dt)
{
	mClickableList.update(dt);
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			std::cout << "Left Clicked " << announcement.id << "\n";
			switch (announcement.id) {
				case MenuState::ClickableID::Play: {
					requestStackPop();
					requestStackPush(States::Game);
				}
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

		
		
	if (event.key.code == sf::Keyboard::Return)
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
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	FOREACH(sf::Text & text, mOptions)
		text.setColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}
