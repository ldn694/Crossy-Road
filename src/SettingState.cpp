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

SettingState::SettingState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context), mOptions(), mOptionIndex(0), mClickableList(context),mScrollBarList()
{

	sf::Texture &texture = context.textures->get(Textures::SettingBackground);
	sf::Font &font = context.fonts->get(Fonts::Main);
    context.textures->load(Textures::Sound, "Assets/Images/sound.png");
	context.textures->load(Textures::Sound_, "Assets/Images/sound_hover.png");
	context.textures->load(Textures::Music, "Assets/Images/music.png");
	context.textures->load(Textures::Music_, "Assets/Images/music_hover.png");
	context.textures->load(Textures::Back, "Assets/Images/back.png");
	context.textures->load(Textures::Back_, "Assets/Images/back_hover.png");
	
	context.textures->load(Textures::MoveLeft, "Assets/Images/MoveLeft_.png");
	context.textures->load(Textures::MoveLeft_, "Assets/Images/MoveLeft.png");
	context.textures->load(Textures::MoveRight, "Assets/Images/MoveRight_.png");
	context.textures->load(Textures::MoveRight_, "Assets/Images/MoveRight.png");
	context.textures->load(Textures::MoveUp, "Assets/Images/MoveUp_.png");
	context.textures->load(Textures::MoveUp_, "Assets/Images/MoveUp.png");
	context.textures->load(Textures::MoveDown_, "Assets/Images/MoveDown.png");
	context.textures->load(Textures::MoveDown, "Assets/Images/MoveDown_.png");

	context.textures->load(Textures::P11,"Assets/Images/keybinding.png");
	context.textures->load(Textures::P12,"Assets/Images/keybinding.png");
	context.textures->load(Textures::P13,"Assets/Images/keybinding.png");
	context.textures->load(Textures::P14,"Assets/Images/keybinding.png");

	context.textures->load(Textures::P21,"Assets/Images/keybinding.png");
	context.textures->load(Textures::P22,"Assets/Images/keybinding.png");
	context.textures->load(Textures::P23,"Assets/Images/keybinding.png");
	context.textures->load(Textures::P24,"Assets/Images/keybinding.png");

    context.textures->load(Textures::SetPlayer1,"Assets/Images/P1.png");
	context.textures->load(Textures::SetPlayer2,"Assets/Images/P2.png");
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(1050.0f / mBackgroundSprite.getGlobalBounds().width, 600.0f / mBackgroundSprite.getGlobalBounds().height);
    
	
	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;
	info.floatList = { 295, 400, 220, 90, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);      //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::Sound_, Textures::Sound};	//cac nut
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Sound, info);

	info.floatList = {300, 500, 220, 90, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Music_, Textures::Music };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Music, info);

	info.floatList = {0, 0, 200, 90, 15};//300
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::Back_, Textures::Back };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::Back, info);

	info.floatList = { 295, 180, 110, 45, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);      //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::MoveLeft_, Textures::MoveLeft};	//cac nut
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::MoveLeft, info);

	info.floatList = {300, 235, 110, 45, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::MoveRight_, Textures::MoveRight };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::MoveRight, info);

	info.floatList = {295, 285, 110, 45, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::MoveUp_, Textures::MoveUp };
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::MoveUp, info);

	info.floatList = {300, 340, 110, 45, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::MoveDown_, Textures::MoveDown};
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::MoveDown, info);
	 
	 //load date from text file
	 std::ifstream fin("Assets/Files/Settings.txt");
	 std::vector<std::string> data;
	 if(fin.is_open())
	 {
		while(!fin.eof())
		{
			std::string word;
			fin>>word;
			data.push_back(word);
		}
	 }
	 fin.close();

	 info.floatList = { 680, 130, 110, 45, 15 };				
	info.status = Clickable::Status(true, true, true);      					
	info.textureIDList = { Textures::SetPlayer1, Textures::SetPlayer1};	
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::SetPlayer1, info);

    info.floatList = { 850, 130, 110, 45, 15 };			
	info.status = Clickable::Status(true, true, true);      				
	info.textureIDList = { Textures::SetPlayer2, Textures::SetPlayer2};	
	info.stringList = { "" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::SetPlayer2, info);



	info.floatList = { 680, 180, 110, 45, 15 };				
	info.status = Clickable::Status(true, true, true);      					
	info.textureIDList = { Textures::P11, Textures::P11};	
	info.stringList = { data[7] };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::P11, info);

	info.floatList = {680, 235, 110, 45, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::P12, Textures::P12 };
	info.stringList = { data[9] };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::P12, info);

	info.floatList = {680, 285, 110, 45, 15};//270
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::P13, Textures::P13 };
	info.stringList = { data[11] };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::P13, info);

	info.floatList = {680, 340, 110, 45, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::P14, Textures::P14};
	info.stringList = { data[13] };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::P14, info);

	info.floatList = { 850, 180, 110, 45, 15 };				//toa do (x,y, +x, +y, scale/10)
	info.status = Clickable::Status(true, true, true);      //cac trang thai duoc cho phep cua button					
	info.textureIDList = { Textures::P21, Textures::P21};	//cac nut
	info.stringList = { data[16] };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::P21, info);

	info.floatList = {850, 235, 110, 45, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::P22, Textures::P22 };
	info.stringList = { data[18] };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::P22, info);

	info.floatList = {850, 285, 110, 45, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::P23, Textures::P23 };
	info.stringList = { data[20] };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::P23, info);

	info.floatList = {850, 340, 110, 45, 15};
	info.status = Clickable::Status(true, true, true);
	info.textureIDList = { Textures::P24, Textures::P24};
	info.stringList = { data[22] };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, ClickableID::P24, info);

    c[0] = c[1] = c[2] = c[3] = c[4] = c[5] = c[6] = c[7] = false;

}

void SettingState::draw()
{
	sf::RenderWindow &window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text &text, mOptions)
	window.draw(text);
	mClickableList.draw();
	mScrollBarList.draw(window);
}

bool SettingState::update(sf::Time dt) 
{
	mClickableList.update(dt);
	float x = mScrollBarList.getVolumeMusic();
	getContext().backgroundmusic->setVolume(100.f*x);
	return true;
}

bool SettingState::handleEvent(const sf::Event &event)
{
	
	sf::RenderWindow &window = *getContext().window;
	mScrollBarList.handleEvent(event,window);
	//mSB_Sound.update(window);
	//mSB_Music.update(window);
     if(event.type == sf::Event::KeyPressed)
	{
		for(int i =0;i<8;i++)
		{
			if(c[i])
			{
				std::string key_string = keyCodeToString(event.key.code);
				std::cout<<key_string<<std::endl;
				mClickableList.setTextByID(i+7,key_string);
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
				case SettingState::ClickableID::P11:
				{
                    c[0] = true; c[1] = c[2] = c[3] = c[4] = c[5] = c[6] = c[7] = false;
				    break;
				}
				case SettingState::ClickableID::P12:
				{
                    c[1] = true; c[0] = c[2] = c[3] = c[4] = c[5] = c[6] = c[7] = false;
					break;
				}
				case SettingState::ClickableID::P13:
				{
                    c[2] = true; c[1] = c[0] = c[3] = c[4] = c[5] = c[6] = c[7] = false;
					break;
				}
				case SettingState::ClickableID::P14:
				{
                    c[3] = true; c[1] = c[2] = c[0] = c[4] = c[5] = c[6] = c[7] = false;
					break;
				}
				case SettingState::ClickableID::P21:
				{
                    c[4] = true; c[1] = c[2] = c[3] = c[0] = c[5] = c[6] = c[7] = false;
					break;
				}
				case SettingState::ClickableID::P22:
				{
                    c[5] = true; c[1] = c[2] = c[3] = c[4] = c[0] = c[6] = c[7] = false;
					break;
				}
				case SettingState::ClickableID::P23:
				{
                    c[6] = true; c[1] = c[2] = c[3] = c[4] = c[5] = c[0] = c[7] = false;
					break;
				}
				case SettingState::ClickableID::P24:
				{
                    c[7] = true; c[1] = c[2] = c[3] = c[4] = c[5] = c[6] = c[0] = false;
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

std::string SettingState::keyCodeToString(sf::Keyboard::Key keyCode) {
    switch (keyCode) {
        case sf::Keyboard::A: return "A";
        case sf::Keyboard::B: return "B";
        case sf::Keyboard::C: return "C";
        case sf::Keyboard::D: return "D";
        case sf::Keyboard::E: return "E";
        case sf::Keyboard::F: return "F";
        case sf::Keyboard::G: return "G";
        case sf::Keyboard::H: return "H";
        case sf::Keyboard::I: return "I";
        case sf::Keyboard::J: return "J";
        case sf::Keyboard::K: return "K";
        case sf::Keyboard::L: return "L";
        case sf::Keyboard::M: return "M";
        case sf::Keyboard::N: return "N";
        case sf::Keyboard::O: return "O";
        case sf::Keyboard::P: return "P";
        case sf::Keyboard::Q: return "Q";
        case sf::Keyboard::R: return "R";
        case sf::Keyboard::S: return "S";
        case sf::Keyboard::T: return "T";
        case sf::Keyboard::U: return "U";
        case sf::Keyboard::V: return "V";
        case sf::Keyboard::W: return "W";
        case sf::Keyboard::X: return "X";
        case sf::Keyboard::Y: return "Y";
        case sf::Keyboard::Z: return "Z";
        case sf::Keyboard::Num0: return "0";
        case sf::Keyboard::Num1: return "1";
        case sf::Keyboard::Num2: return "2";
        case sf::Keyboard::Num3: return "3";
        case sf::Keyboard::Num4: return "4";
        case sf::Keyboard::Num5: return "5";
        case sf::Keyboard::Num6: return "6";
        case sf::Keyboard::Num7: return "7";
        case sf::Keyboard::Num8: return "8";
        case sf::Keyboard::Num9: return "9";
        case sf::Keyboard::Escape: return "Escape";
        case sf::Keyboard::LControl: return "Left Control";
        case sf::Keyboard::LShift: return "Left Shift";
        case sf::Keyboard::LAlt: return "Left Alt";
        case sf::Keyboard::LSystem: return "Left System";
        case sf::Keyboard::RControl: return "Right Control";
        case sf::Keyboard::RShift: return "Right Shift";
        case sf::Keyboard::RAlt: return "Right Alt";
        case sf::Keyboard::RSystem: return "Right System";
        case sf::Keyboard::Menu: return "Menu";
        case sf::Keyboard::LBracket: return "[";
        case sf::Keyboard::RBracket: return "]";
        case sf::Keyboard::Semicolon: return ";";
        case sf::Keyboard::Comma: return ",";
        case sf::Keyboard::Period: return ".";
        case sf::Keyboard::Quote: return "'";
        case sf::Keyboard::Slash: return "/";
        case sf::Keyboard::Backslash: return "\\";
        case sf::Keyboard::Tilde: return "~";
        case sf::Keyboard::Equal: return "=";
        case sf::Keyboard::Hyphen: return "-";
        case sf::Keyboard::Space: return "Space";
        case sf::Keyboard::Enter: return "Enter";
        case sf::Keyboard::Backspace: return "Backspace";
        case sf::Keyboard::Tab: return "Tab";
        case sf::Keyboard::PageUp: return "Page Up";
        case sf::Keyboard::PageDown: return "Page Down";
        case sf::Keyboard::End: return "End";
        case sf::Keyboard::Home: return "Home";
        case sf::Keyboard::Insert: return "Insert";
        case sf::Keyboard::Delete: return "Delete";
        case sf::Keyboard::Add: return "+";
        case sf::Keyboard::Subtract: return "-";
        case sf::Keyboard::Multiply: return "*";
        case sf::Keyboard::Divide: return "/";
        case sf::Keyboard::Left: return "Left";
        case sf::Keyboard::Right: return "Right";
        case sf::Keyboard::Up: return "Up";
        case sf::Keyboard::Down: return "Down";
        case sf::Keyboard::Numpad0: return "Numpad 0";
        case sf::Keyboard::Numpad1: return "Numpad 1";
        case sf::Keyboard::Numpad2: return "Numpad 2";
        case sf::Keyboard::Numpad3: return "Numpad 3";
        case sf::Keyboard::Numpad4: return "Numpad 4";
        case sf::Keyboard::Numpad5: return "Numpad 5";
        case sf::Keyboard::Numpad6: return "Numpad 6";
        case sf::Keyboard::Numpad7: return "Numpad 7";
        case sf::Keyboard::Numpad8: return "Numpad 8";
        case sf::Keyboard::Numpad9: return "Numpad 9";
        case sf::Keyboard::F1: return "F1";
        case sf::Keyboard::F2: return "F2";
        case sf::Keyboard::F3: return "F3";
        case sf::Keyboard::F4: return "F4";
        case sf::Keyboard::F5: return "F5";
        case sf::Keyboard::F6: return "F6";
        case sf::Keyboard::F7: return "F7";
        case sf::Keyboard::F8: return "F8";
        case sf::Keyboard::F9: return "F9";
        case sf::Keyboard::F10: return "F10";
        case sf::Keyboard::F11: return "F11";
        case sf::Keyboard::F12: return "F12";
        case sf::Keyboard::F13: return "F13";
        case sf::Keyboard::F14: return "F14";
        case sf::Keyboard::F15: return "F15";
        case sf::Keyboard::Pause: return "Pause";
        default: return "Unknown";
    }
}

sf::Keyboard::Key SettingState::stringToSFMLKey(const std::string& keyString) {
    static const std::unordered_map<std::string, sf::Keyboard::Key> keyMap = {
        {"A", sf::Keyboard::A},
        {"B", sf::Keyboard::B},
        {"C", sf::Keyboard::C},
        {"D", sf::Keyboard::D},
        {"E", sf::Keyboard::E},
        {"F", sf::Keyboard::F},
        {"G", sf::Keyboard::G},
        {"H", sf::Keyboard::H},
        {"I", sf::Keyboard::I},
        {"J", sf::Keyboard::J},
        {"K", sf::Keyboard::K},
        {"L", sf::Keyboard::L},
        {"M", sf::Keyboard::M},
        {"N", sf::Keyboard::N},
        {"O", sf::Keyboard::O},
        {"P", sf::Keyboard::P},
        {"Q", sf::Keyboard::Q},
        {"R", sf::Keyboard::R},
        {"S", sf::Keyboard::S},
        {"T", sf::Keyboard::T},
        {"U", sf::Keyboard::U},
        {"V", sf::Keyboard::V},
        {"W", sf::Keyboard::W},
        {"X", sf::Keyboard::X},
        {"Y", sf::Keyboard::Y},
        {"Z", sf::Keyboard::Z},
        {"Num0", sf::Keyboard::Num0},
        {"Num1", sf::Keyboard::Num1},
        {"Num2", sf::Keyboard::Num2},
        {"Num3", sf::Keyboard::Num3},
        {"Num4", sf::Keyboard::Num4},
        {"Num5", sf::Keyboard::Num5},
        {"Num6", sf::Keyboard::Num6},
        {"Num7", sf::Keyboard::Num7},
        {"Num8", sf::Keyboard::Num8},
        {"Num9", sf::Keyboard::Num9},
        {"Escape", sf::Keyboard::Escape},
        {"LControl", sf::Keyboard::LControl},
        {"LShift", sf::Keyboard::LShift},
        {"LAlt", sf::Keyboard::LAlt},
        {"LSystem", sf::Keyboard::LSystem},
        {"RControl", sf::Keyboard::RControl},
        {"RShift", sf::Keyboard::RShift},
        {"RAlt", sf::Keyboard::RAlt},
        {"RSystem", sf::Keyboard::RSystem},
        {"Menu", sf::Keyboard::Menu},
        {"LBracket", sf::Keyboard::LBracket},
        {"RBracket", sf::Keyboard::RBracket},
        {"SemiColon", sf::Keyboard::SemiColon},
        {"Comma", sf::Keyboard::Comma},
        {"Period", sf::Keyboard::Period},
        {"Quote", sf::Keyboard::Quote},
        {"Slash", sf::Keyboard::Slash},
        {"BackSlash", sf::Keyboard::BackSlash},
        {"Tilde", sf::Keyboard::Tilde},
        {"Equal", sf::Keyboard::Equal},
        {"Dash", sf::Keyboard::Dash},
        {"Space", sf::Keyboard::Space},
        {"Return", sf::Keyboard::Return},
        {"BackSpace", sf::Keyboard::BackSpace},
        {"Tab", sf::Keyboard::Tab},
        {"PageUp", sf::Keyboard::PageUp},
        {"PageDown", sf::Keyboard::PageDown},
        {"End", sf::Keyboard::End},
        {"Home", sf::Keyboard::Home},
        {"Insert", sf::Keyboard::Insert},
        {"Delete", sf::Keyboard::Delete},
        {"Add", sf::Keyboard::Add},
        {"Subtract", sf::Keyboard::Subtract},
        {"Multiply", sf::Keyboard::Multiply},
        {"Divide", sf::Keyboard::Divide},
        {"Left", sf::Keyboard::Left},
        {"Right", sf::Keyboard::Right},
        {"Up", sf::Keyboard::Up},
        {"Down", sf::Keyboard::Down},
        {"Numpad0", sf::Keyboard::Numpad0},
        {"Numpad1", sf::Keyboard::Numpad1},
        {"Numpad2", sf::Keyboard::Numpad2},
        {"Numpad3", sf::Keyboard::Numpad3},
        {"Numpad4", sf::Keyboard::Numpad4},
        {"Numpad5", sf::Keyboard::Numpad5},
        {"Numpad6", sf::Keyboard::Numpad6},
        {"Numpad7", sf::Keyboard::Numpad7},
        {"Numpad8", sf::Keyboard::Numpad8},
        {"Numpad9", sf::Keyboard::Numpad9},
        {"F1", sf::Keyboard::F1},
        {"F2", sf::Keyboard::F2},
        {"F3", sf::Keyboard::F3},
        {"F4", sf::Keyboard::F4},
        {"F5", sf::Keyboard::F5},
        {"F6", sf::Keyboard::F6},
        {"F7", sf::Keyboard::F7},
        {"F8", sf::Keyboard::F8},
        {"F9", sf::Keyboard::F9},
        {"F10", sf::Keyboard::F10},
        {"F11", sf::Keyboard::F11},
        {"F12", sf::Keyboard::F12},
        {"F13", sf::Keyboard::F13},
        {"F14", sf::Keyboard::F14},
        {"F15", sf::Keyboard::F15},
        {"Pause", sf::Keyboard::Pause},
        {"KeyCount", sf::Keyboard::KeyCount},
        {"Unknown", sf::Keyboard::Unknown}
    };

    auto it = keyMap.find(keyString);
    if (it != keyMap.end()) 
	{
        return it->second;
    } else
	 {
        
        return sf::Keyboard::Unknown;
    }
}

SettingState::~SettingState()
{
	// save to text file
	std::ofstream fout("Assets/Files/Settings.txt",std::ios::trunc);
	if(fout.is_open())
	{
		fout<<"Sound: "<<mScrollBarList.getVolumeSound()<<" "<<"Music: "<<mScrollBarList.getVolumeMusic()<<"\n";
		fout<<"Player 1\n ";
		fout<<"MoveLeft: "<<mClickableList.getTextByID(7)<<" MoveRight: "<<mClickableList.getTextByID(8)<<" MoveUp: "<<mClickableList.getTextByID(9)<<" MoveDown: "<<mClickableList.getTextByID(10)<<"\n";
		fout<<"Player2\n";
		fout<<"MoveLeft: "<<mClickableList.getTextByID(11)<<" MoveRight: "<<mClickableList.getTextByID(12)<<" MoveUp: "<<mClickableList.getTextByID(13)<<" MoveDown: "<<mClickableList.getTextByID(14)<<"\n";
	}
	fout.close();

}
