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

	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(1050.0f / mBackgroundSprite.getGlobalBounds().width, 600.0f / mBackgroundSprite.getGlobalBounds().height);
	
	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 165, 225, 300, 100, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);          //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::Play, Textures::Play_};	//cac nut
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Play, info);

	info.floatList = {580, 225, 320, 100, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Load, Textures::Load_};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Load, info);

	info.floatList = {160, 325, 320, 100, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Score, Textures::Score_};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Score, info);

	info.floatList = {575, 325, 320, 100, 15};
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

	info.floatList = {590, 340, 120, 70, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Exit, Textures::Exit_};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Exit, info);

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
	return false;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			// std::cerr << "Left Clicked " << announcement.id << "\n";
			switch (announcement.id) {
				case MenuState::ClickableID::Play: {
					requestStackPop();
					requestStackPush(States::GameStart);
					break;
				}
				case MenuState::ClickableID::Set: {
					requestStackPush(States::Setting);
					break;
				}
				case MenuState::ClickableID::Load: {
					int Size = getStackSize();
					if (Size != 1) {
						getContext().music->stopAllMusic();
						requestStackPop();
						requestStackPush(States::Loading);
					}
					break;
				}
				case MenuState::ClickableID::Score: {
					requestStackPush(States::Scoreboard);
					break;
				}
				case MenuState::ClickableID::Exit: {
					requestStateClear();
					break;
				}
			}
		}
		else if (announcement.action == Clickable::RightPressed) {
			// std::cerr << "Right Clicked " << announcement.id << "\n";
		}
	}
	while (pendingNotification()) {
		State::Info info = popNotification();
		// std::cerr << info.stringList[0] << "\n";
	}
	if (event.type == sf::Event::MouseButtonPressed) {

	}
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;


	return false;
}