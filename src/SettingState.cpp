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
#include "ScrollBarList.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include<iomanip>

const std::string SettingState::mSettingsPath = "Assets/Files/Settings.txt";

bool SettingState::checkValidSettings(const std::string& filename) {
	std::ifstream fin(filename);
	std::vector<std::string> data;
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string word;
			fin >> word;
			data.push_back(word);
		}
	}
	fin.close();
	while (data.size() > 0 && data.back() == "" || data.back() == "\n" || data.back() == "\r" || data.back() == " ") {
		data.pop_back();
	}
	if (data.size() != 24) {
		std::cout << "Invalid data size\n";
		for (int i = 0; i < data.size(); i++) {
			std::cout << data[i] << "\n";
		}
		return false;
	}
	//Must be the same letter
	if (data[0] != "Sound:" || 
		data[2] != "Music:" || 
		data[4] != "Player" || data[5] != "1" || 
		data[6] != "MoveLeft:" || 
		data[8] != "MoveRight:" || 
		data[10] != "MoveUp:" || 
		data[12] != "MoveDown:" || 
		data[14] != "Player" || 
		data[15] != "2" || 
		data[16] != "MoveLeft:" || 
		data[18] != "MoveRight:" || 
		data[20] != "MoveUp:" || 
		data[22] != "MoveDown:") {
		std::cout << "Invalid const string data\n";
		return false;
	}
	//Sound and Music must be a float from 0 to 1
	if (std::stof(data[1]) < 0 || std::stof(data[1]) > 1 || std::stof(data[3]) < 0 || std::stof(data[3]) > 1) {
		std::cout << "Invalid sound or music data\n";
		return false;
	}
	//Player 1 and 2 must be a valid key
	int player1[4] = { 7, 9, 11, 13 };
	int player2[4] = { 17, 19, 21, 23 };
	for (int i = 0; i < 4; i++) {
		if (stringToSFMLKey(data[player1[i]]) == sf::Keyboard::Unknown || stringToSFMLKey(data[player2[i]]) == sf::Keyboard::Unknown) {
			std::cout << "Invalid key data\n";
			return false;
		}
	}
	return true;
}

void SettingState::createDefaultData() {
	std::ofstream fout(SettingState::mSettingsPath, std::ios::trunc);
	if (fout.is_open())
	{
		fout << "Sound: 1.00 ";
		fout << "Music: 1.00\n";
		fout << "Player 1\n";
		fout << "MoveLeft: " << "A" << " ";
		fout << "MoveRight: " << "D" << " ";
		fout << "MoveUp: " << "W" << " ";
		fout << "MoveDown: " << "S" << "\n";
		fout << "Player 2\n";
		fout << "MoveLeft: " << "Left" << " ";
		fout << "MoveRight: " << "Right" << " ";
		fout << "MoveUp: " << "Up" << " ";
		fout << "MoveDown: " << "Down";
	}
	fout.close();
	mPendingUpdate = true;
}

std::string SettingState::getData(std::vector<std::string>& data, Data type)
{
	switch (type)
	{
	case Data::SoundVolume:
	{
		return data[1];
		break;
	}
	case Data::MusicVolume:
	{
		return data[3];
		break;
	}
	case Data::P1Left:
	{
		return data[7];
		break;
	}
	case Data::P1Right:
	{
		return data[9];
		break;
	}
	case Data::P1Up:
	{
		return data[11];
		break;
	}
	case Data::P1Down:
	{
		return data[13];
		break;
	}
	case Data::P2Left:
	{
		return data[17];
		break;
	}
	case Data::P2Right:
	{
		return data[19];
		break;
	}
	case Data::P2Up:
	{
		return data[21];
		break;
	}
	case Data::P2Down:
	{
		return data[23];
		break;
	}
	}
	return "Unknown";
}

bool SettingState::mPendingUpdate = false;

bool SettingState::pendingUpdated() {
	bool res = mPendingUpdate;
	mPendingUpdate = false;
	return res;
}

SettingState::SettingState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context), mOptions(), mOptionIndex(0), mClickableList(context)
{
	if (!checkValidSettings(mSettingsPath)) {
		std::cout << "Creating default settings\n";
		createDefaultData();
	}
	mScrollBarList = std::move(ScrollBarList(mSettingsPath));
	sf::Texture& texture = context.textures->get(Textures::SettingBackground);
	sf::Font& font = context.fonts->get(Fonts::Main);
	context.textures->load(Textures::Sound, "Assets/Images/sound.png");
	context.textures->load(Textures::Sound_, "Assets/Images/sound_hover.png");
	context.textures->load(Textures::Music, "Assets/Images/music.png");
	context.textures->load(Textures::Music_, "Assets/Images/music_hover.png");
	context.textures->load(Textures::Back, "Assets/Images/back.png");
	context.textures->load(Textures::Back_, "Assets/Images/back_hover.png");
	context.textures->load(Textures::scoreboard_quit, "Assets/Images/ForScore/quit.png");
	context.textures->load(Textures::scoreboard_quit_hover, "Assets/Images/ForScore/quit_hover.png");

	context.textures->load(Textures::MoveLeft, "Assets/Images/MoveLeft_.png");
	context.textures->load(Textures::MoveLeft_, "Assets/Images/MoveLeft.png");
	context.textures->load(Textures::MoveRight, "Assets/Images/MoveRight_.png");
	context.textures->load(Textures::MoveRight_, "Assets/Images/MoveRight.png");
	context.textures->load(Textures::MoveUp, "Assets/Images/MoveUp_.png");
	context.textures->load(Textures::MoveUp_, "Assets/Images/MoveUp.png");
	context.textures->load(Textures::MoveDown_, "Assets/Images/MoveDown.png");
	context.textures->load(Textures::MoveDown, "Assets/Images/MoveDown_.png");

	context.textures->load(Textures::KeyBinding, "Assets/Images/keybinding.png");
	context.textures->load(Textures::KeyBinding_, "Assets/Images/keybinding_.png");

	context.textures->load(Textures::SetPlayer1, "Assets/Images/P1.png");
	context.textures->load(Textures::SetPlayer2, "Assets/Images/P2.png");
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(1050.0f / mBackgroundSprite.getGlobalBounds().width, 600.0f / mBackgroundSprite.getGlobalBounds().height);


	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 295, 400, 220, 90, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);      //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::Sound_, Textures::Sound };	//cac nut
	info.stringList = { "" };
	info.fontIDList = { Fonts::Bungee };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Sound, info);

	info.floatList = { 300, 500, 220, 90, 15 };
	info.textureIDList = { Textures::Music_, Textures::Music };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Music, info);

	info.floatList = {30, 13, 70, 70, 15};
	info.textureIDList = { Textures::scoreboard_quit, Textures::scoreboard_quit_hover };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Back, info);

	info.floatList = { 295, 180, 110, 45, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(Clickable::Status(true, false, false));
	info.textureIDList = { Textures::MoveLeft_, Textures::MoveLeft };	//cac nut
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::MoveLeft, info);

	info.floatList = { 300, 235, 110, 45, 15 };
	info.status = Clickable::Status(Clickable::Status(true, false, false));
	info.textureIDList = { Textures::MoveRight_, Textures::MoveRight };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::MoveRight, info);

	info.floatList = { 295, 285, 110, 45, 15 };
	info.status = Clickable::Status(Clickable::Status(true, false, false));
	info.textureIDList = { Textures::MoveUp_, Textures::MoveUp };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::MoveUp, info);

	info.floatList = { 300, 340, 110, 45, 15 };
	info.status = Clickable::Status(Clickable::Status(true, false, false));
	info.textureIDList = { Textures::MoveDown_, Textures::MoveDown };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::MoveDown, info);

	info.floatList = { 680, 130, 110, 45, 15 };				
	info.status = Clickable::Status(Clickable::Status(true, false, false));      					
	info.textureIDList = { Textures::SetPlayer1, Textures::SetPlayer1};	
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::SetPlayer1, info);

    info.floatList = { 850, 130, 110, 45, 15 };			
	info.status = Clickable::Status(Clickable::Status(true, false, false));      				
	info.textureIDList = { Textures::SetPlayer2, Textures::SetPlayer2};	
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::SetPlayer2, info);

	//load date from text file
	std::ifstream fin(mSettingsPath);
	mData.clear();
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string word;
			fin >> word;
			mData.push_back(word);
		}
	}
	fin.close();

	for (int playerID = 0; playerID < 2; playerID++) {
		for (int moveID = 0; moveID < 4; moveID++) {
			int id = playerID * 4 + moveID;
			info.floatList = { 680.f + 170 * playerID, 180.f + 55 * moveID, 110, 45, 15 };
			info.status = Clickable::Status(true, true, true);
			info.textureIDList = { Textures::KeyBinding, Textures::KeyBinding_ };
			info.stringList = { getData(mData, static_cast<Data>(id + Data::P1Left)) };
			info.fontIDList = { Fonts::Bungee };
			info.colorList = { sf::Color::White };
			mClickableList.addClickable(Clickable::Type::Button, ClickableID::PlayerOneMoveLeft + id, info);
		}
	}

	for (int i = 0; i < 8; i++) {
		c[i] = false;
	}

}

void SettingState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text & text, mOptions)
		window.draw(text);
	mClickableList.draw();
	mScrollBarList.draw(window);
}

bool SettingState::update(sf::Time dt)
{
	mClickableList.update(dt);
	return true;
}

bool SettingState::handleEvent(const sf::Event& event)
{

	sf::RenderWindow& window = *getContext().window;
	if (mScrollBarList.handleEvent(event, window)) {
		mPendingUpdate = true;
	}
	//mSB_Sound.update(window);
	//mSB_Music.update(window);
	if (event.type == sf::Event::KeyPressed)
	{
		for (int i = 0; i < 8;i++)
		{
			if (c[i])
			{
				std::string key_string = keyCodeToString(event.key.code);
				std::cout << key_string << std::endl;
				mClickableList.setTextByID(i + ClickableID::PlayerOneMoveLeft, key_string);
				mPendingUpdate = true;
				//std::string test = mClickableList.getTextByID(i+7);
				//std::cout<<test<<std::endl;
			}
		}
	}
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
			default:
				if (announcement.id >= SettingState::ClickableID::PlayerOneMoveLeft && announcement.id <= SettingState::ClickableID::PlayerTwoMoveDown) {
					for (int i = 0; i < 8; i++) {
						c[i] = false;
					}
					c[announcement.id - SettingState::ClickableID::PlayerOneMoveLeft] = true;
				}
				break;
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

SettingState::~SettingState()
{
	// save to text file
	std::ofstream fout(mSettingsPath, std::ios::trunc);
	if (fout.is_open())
	{
		fout << std::fixed << std::setprecision(2) << "Sound: " << mScrollBarList.getVolumeSound() << " ";
		fout << std::fixed << std::setprecision(2) << "Music: " << mScrollBarList.getVolumeMusic() << "\n";
		fout << "Player 1\n";
		fout << "MoveLeft: " << mClickableList.getTextByID(ClickableID::PlayerOneMoveLeft) << " ";
		fout << "MoveRight: " << mClickableList.getTextByID(ClickableID::PlayerOneMoveRight) << " ";
		fout << "MoveUp: " << mClickableList.getTextByID(ClickableID::PlayerOneMoveUp) << " ";
		fout << "MoveDown: " << mClickableList.getTextByID(ClickableID::PlayerOneMoveDown) << "\n";
		fout << "Player 2\n";
		fout << "MoveLeft: " << mClickableList.getTextByID(ClickableID::PlayerTwoMoveLeft) << " ";
		fout << "MoveRight: " << mClickableList.getTextByID(ClickableID::PlayerTwoMoveRight) << " ";
		fout << "MoveUp: " << mClickableList.getTextByID(ClickableID::PlayerTwoMoveUp) << " ";
		fout << "MoveDown: " << mClickableList.getTextByID(ClickableID::PlayerTwoMoveDown) << "\n";
	}
	fout.close();

}
