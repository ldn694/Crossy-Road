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
	context.sounds->pauseAllSounds();

	loadTextures(context);
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	
	mBackgroundSprite.setTexture(context.textures->get(Textures::PauseBackground));
	setSize(mBackgroundSprite, viewSize);
	mBackgroundSprite.setColor(sf::Color(255, 255, 255, 200));
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

	info.floatList = { 525 - 65 - 300, 300 - 65, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Home, Textures::Home_Hover };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Home, info);

	info.floatList = { 525 - 65, 300 - 65, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Resume, Textures::Resume_Hover };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Resume, info);

	info.floatList = { 525 - 65 + 300, 300 - 65, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Setting, Textures::Setting_Hover };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Setting, info);
}
void PauseState::loadTextures(Context context)
{
	context.textures->load(Textures::Home, "Assets/Images/ForPause/home_button.png");
	context.textures->load(Textures::Home_Hover, "Assets/Images/ForPause/home_button_hover.png");
	context.textures->load(Textures::Resume, "Assets/Images/ForPause/resume_button.png");
	context.textures->load(Textures::Resume_Hover, "Assets/Images/ForPause/resume_button_hover.png");
	context.textures->load(Textures::Setting, "Assets/Images/ForPause/setting_button.png");
	context.textures->load(Textures::Setting_Hover, "Assets/Images/ForPause/setting_button_hover.png");
	context.textures->load(Textures::PauseBackground, "Assets/Images/ForPause/background.png");
}
void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
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
			// std::cout << "Left Clicked " << announcement.id << "\n";
            if (announcement.id == ButtonNames::Home) {
				requestStackPop();
				requestStackPush(States::Menu);
				//State::Info info;
				//info.stringList = { "Hello from PauseState to MenuState" };
				//requestNotifyState(States::Menu, info);
			}
			else if (announcement.id == ButtonNames::Resume) {
				requestStackPop();
				requestStackPush(States::Loading);
				//State::Info info;
				//requestNotifyState(States::Game, info);
			}
			else if (announcement.id == ButtonNames::Setting) {
				requestStackPush(States::Setting);
				//State::Info info;
				//info.stringList = { "Hello from PauseState to SettingState" };
				//requestNotifyState(States::Setting, info);
			}
		}
		else if (announcement.action == Clickable::RightPressed) {
			// std::cout << "Right Clicked " << announcement.id << "\n";
		}
	}
	while (pendingNotification()) {
		State::Info info = popNotification();
		// std::cout << info.stringList[0] << "\n";
	}
	return false;
}