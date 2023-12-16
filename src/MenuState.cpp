#include "MenuState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>

MenuState::MenuState(StateStack &stack, Context context)
	: State(stack, context), mOptions(), mOptionIndex(0), mClickableList(context)
{

	sf::Texture &texture = context.textures->get(Textures::M2);
	sf::Font &font = context.fonts->get(Fonts::T2);

	context.textures->load(Textures::Play, "Assets/Images/Play.PNG");
	context.textures->load(Textures::Play_, "Assets/Images/Play_.PNG");
	context.textures->load(Textures::Load, "Assets/Images/Load.PNG");
	context.textures->load(Textures::Load_, "Assets/Images/Load_.PNG");
	context.textures->load(Textures::Score, "Assets/Images/Score.PNG");
	context.textures->load(Textures::Score_, "Assets/Images/Score_.PNG");
	context.textures->load(Textures::Set, "Assets/Images/Setting.PNG");
	context.textures->load(Textures::Set_, "Assets/Images/Setting_.PNG");
	context.textures->load(Textures::Exit, "Assets/Images/Exit.PNG");
	context.textures->load(Textures::Exit_, "Assets/Images/Exit_.PNG");

	
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(0.55, 0.55);
	
	// A simple menu demonstration
	/*
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("New Game");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f - sf::Vector2f(0.f, 60.f));
	
	mOptions.push_back(playOption);

	sf::Text loadOption;
	loadOption.setFont(font);
	loadOption.setString("Load Game");
	centerOrigin(loadOption);
	loadOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 80.f));
	mOptions.push_back(loadOption);

	sf::Text scoreBoard;
	scoreBoard.setFont(font);
	scoreBoard.setString("Scoreboard");
	centerOrigin(scoreBoard);
	scoreBoard.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 160.f));
	mOptions.push_back(scoreBoard);

	sf::Text setting;
	setting.setFont(font);
	setting.setString("Setting");
	centerOrigin(setting);
	setting.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 240.f));
	mOptions.push_back(setting);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 320.f));
	mOptions.push_back(exitOption);

	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 0, 0, 100, 100, 10 };
	info.stringList = { "Button 0" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Button, Textures::PressedButton };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Button1, info);

	info.floatList = {500, 200, 70, 70, 10};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Button, Textures::PressedButton };
	info.stringList = { "Button 1" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Button2, info);
	*/

	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 255, 240, 220, 70, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);      //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::Play_, Textures::Play};	//cac nut
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Play, info);

	info.floatList = {260, 340, 220, 70, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Load_, Textures::Load };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Load, info);

	info.floatList = {260, 440, 240, 70, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Score_, Textures::Score };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Score, info);

	info.floatList = {580, 240, 220, 70, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Set, Textures::Set_};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Set, info);

	info.floatList = {590, 340, 120, 70, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Exit_, Textures::Exit };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Exit, info);

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow &window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text &text, mOptions)
	window.draw(text);
	mClickableList.draw();
}

bool MenuState::update(sf::Time dt)
{
	mClickableList.update(dt);
	return true;
}

bool MenuState::handleEvent(const sf::Event &event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			std::cout << "Left Clicked " << announcement.id << "\n";
			switch (announcement.id) {
				case MenuState::ClickableID::Play: {
					requestStackPush(States::Game);
				}
			}
		}
		else if (announcement.action == Clickable::RightPressed) {
			std::cout << "Right Clicked " << announcement.id << "\n";
		}
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
