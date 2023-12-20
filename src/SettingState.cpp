#include"State.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include "StateIdentifiers.hpp"
#include "SettingState.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <StateIdentifiers.hpp>

#include<iostream>
#include<string>

SettingState::SettingState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context), mOptions(), mOptionIndex(0), mClickableList(context)
{

	sf::Texture &texture = context.textures->get(Textures::SettingBackground);
	sf::Font &font = context.fonts->get(Fonts::Main);
    context.textures->load(Textures::Sound, "Assets/Images/Play.PNG");
	context.textures->load(Textures::Sound_, "Assets/Images/Play_.PNG");
	context.textures->load(Textures::Music, "Assets/Images/Load.PNG");
	context.textures->load(Textures::Music_, "Assets/Images/Load_.PNG");
	context.textures->load(Textures::Back, "Assets/Images/Score.PNG");
	context.textures->load(Textures::Back_, "Assets/Images/Score_.PNG");
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(1050.0f / mBackgroundSprite.getGlobalBounds().width, 600.0f / mBackgroundSprite.getGlobalBounds().height);
    
	
	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 295, 240, 220, 70, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);      //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::Sound_, Textures::Sound};	//cac nut
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Sound, info);

	info.floatList = {300, 340, 220, 70, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Music_, Textures::Music };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Music, info);

	info.floatList = {400, 440, 240, 70, 15};//300
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Back_, Textures::Back };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Back, info);
}

void SettingState::draw()
{
	sf::RenderWindow &window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text &text, mOptions)
	window.draw(text);
	mClickableList.draw();
}

bool SettingState::update(sf::Time dt) 
{
	mClickableList.update(dt);
	return true;
}

bool SettingState::handleEvent(const sf::Event &event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			std::cout << "Left Clicked " << announcement.id << "\n";
			switch (announcement.id) {
				case SettingState::ClickableID::Sound: {
					
					break;
				}
				case SettingState::ClickableID::Music: {
					
					break;
				}
				case SettingState::ClickableID::Back: {
					requestStackPop();
					break;
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
	return false;
}

