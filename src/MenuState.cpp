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
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Main);
	context.textures->load(Textures::Button, "Assets/Images/Button.png");
	context.textures->load(Textures::PressedButton, "Assets/Images/PressedButton.png");
	context.textures->load(Textures::Choice, "Assets/Images/Choice.png");
	context.textures->load(Textures::PressedChoice, "Assets/Images/Button.png");
	context.textures->load(Textures::HoveredChoice, "Assets/Images/HoveredChoice.png");

	mBackgroundSprite.setTexture(texture);

	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(exitOption);

	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 0, 0, 100, 100, 10 };
	info.stringList = { "Button 0" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Button, Textures::PressedButton };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, 0, info);

	info.floatList = { 500, 200, 120, 120, 10 };
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Button, Textures::PressedButton };
	info.stringList = { "GAME START" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, 1, info);

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
			if (announcement.id == 0){
				requestStackPop();
				State::Info info;
				info.stringList = {"Start from clicking on " + std::to_string(announcement.id) + " button.\n"};
				requestStackPush(States::Game, info);
			} else{
				requestStackPop();
				State::Info info;
				info.stringList = {"Start from clicking on " + std::to_string(announcement.id) + " button.\n"};
				requestStackPush(States::GameStart, info);
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
