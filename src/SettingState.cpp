#include"State.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include "StateIdentifiers.hpp"
#include "SettingState.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Audio.hpp>
#include <StateIdentifiers.hpp>
#include "ScrollBar.hpp"
#include<iostream>
#include<fstream>
#include<string>

SettingState::SettingState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context), mOptions(), mOptionIndex(0), mClickableList(context),mSB_Sound(),mSB_Music()
{

	sf::Texture &texture = context.textures->get(Textures::SettingBackground);
	sf::Font &font = context.fonts->get(Fonts::Main);
    context.textures->load(Textures::Sound, "Assets/Images/sound.png");
	context.textures->load(Textures::Sound_, "Assets/Images/sound_hover.png");
	context.textures->load(Textures::Music, "Assets/Images/music.png");
	context.textures->load(Textures::Music_, "Assets/Images/music_hover.png");
	context.textures->load(Textures::Back, "Assets/Images/back.png");
	context.textures->load(Textures::Back_, "Assets/Images/back_hover.png");
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(1050.0f / mBackgroundSprite.getGlobalBounds().width, 600.0f / mBackgroundSprite.getGlobalBounds().height);
    
	
	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 295, 240, 220, 90, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);      //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::Sound_, Textures::Sound};	//cac nut
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Sound, info);

	info.floatList = {300, 340, 220, 90, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Music_, Textures::Music };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Music, info);

	info.floatList = {400, 440, 240, 90, 15};//300
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Back_, Textures::Back };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Back, info);

	// create 2 ScrollBar
	// load from file txt
	std::ifstream fin1("Assets/Files/ScrollBar1.txt");
	std::ifstream fin2("Assets/Files/ScrollBar2.txt");
	float a[2];
	a[0] = a[1] = 600;
	if(fin1.is_open())
	{
        fin1>>a[0];
	}
	if(fin2.is_open())
	{
		fin2>>a[1];
	}
	fin1.close();
	fin2.close();
	int num1 = 1;
	int num2 = 2;
	//std::cout<<num1<<" "<<num2<<std::endl;
	ScrollBar x(600.f,270.f,220.f,a[0],num1);
	ScrollBar y(600.f,370.f,220.f,a[1],num2);
	mSB_Sound = x;
	mSB_Music = y;
	//mMusic.openFromFile("Assets/Music/CROSSY.wav");
	//mMusic.setLoop(true);
	//mMusic.setVolume(100.f);
	//mMusic.play();
}

void SettingState::draw()
{
	sf::RenderWindow &window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text &text, mOptions)
	window.draw(text);
	mClickableList.draw();
	mSB_Sound.draw(window);
	mSB_Music.draw(window);
}

bool SettingState::update(sf::Time dt) 
{
	mClickableList.update(dt);
	float x = mSB_Music.getValue();
	getContext().backgroundmusic->setVolume(100.f*x);
	float y = mSB_Sound.getValue();
	*getContext().mVolume = y;
	//std::cout<<y<<std::endl;
	return true;
}

bool SettingState::handleEvent(const sf::Event &event)
{
	sf::RenderWindow &window = *getContext().window;
	mSB_Sound.handleEvent(event,window);
    mSB_Music.handleEvent(event,window);
	//mSB_Sound.update(window);
	//mSB_Music.update(window);
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

