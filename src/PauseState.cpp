#include "PauseState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>


PauseState::PauseState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context),
	mClickableList(context)
{
	loadTextures(context);
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	/*mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(70);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("(Press Backspace to return to the main menu)");
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);*/

	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;

	info.floatList = { 260, 280, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::BackToMenu, Textures::BackToMenu_Hover };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::BackToMenu, info);

	info.floatList = { 260 + 200, 280, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Continue, Textures::Continue_Hover };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Continue, info);

	info.floatList = { 260 + 400, 280, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Setting, Textures::Setting_Hover };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Setting, info);
}
void PauseState::loadTextures(Context context)
{
	context.textures->load(Textures::BackToMenu, "Assets/Images/back_button.png");
	context.textures->load(Textures::BackToMenu_Hover, "Assets/Images/back_button_hover.png");
	context.textures->load(Textures::Continue, "Assets/Images/continue_button.png");
	context.textures->load(Textures::Continue_Hover, "Assets/Images/continue_button_hover.png");
	context.textures->load(Textures::Setting, "Assets/Images/setting_button.png");
	context.textures->load(Textures::Setting_Hover, "Assets/Images/setting_button_hover.png");
}
void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	mClickableList.draw();
}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			std::cout << "Left Clicked " << announcement.id << "\n";
            if (announcement.id == ButtonNames::BackToMenu) {
				requestStackPop();
				requestStackPush(States::Menu);
				State::Info info;
				info.stringList = { "Hello from PauseState to MenuState" };
				requestNotifyState(States::Menu, info);
			}
			else if (announcement.id == ButtonNames::Continue) {
				requestStackPop();
				State::Info info;
				//requestNotifyState(States::Game, info);
			}
			else if (announcement.id == ButtonNames::Setting) {
				requestStackPush(States::Setting);
				State::Info info;
				info.stringList = { "Hello from PauseState to SettingState" };
				requestNotifyState(States::Setting, info);
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
	return false;
}