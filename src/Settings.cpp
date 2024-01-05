#include "Settings.hpp"
#include "SettingState.hpp"
#include "Utility.hpp"
#include <fstream>
#include <sstream>

Settings::Settings(Player* player) : mPlayer(player), mMainSounds(nullptr), mGameSounds(nullptr), mMusicPlayer(nullptr) {
    changed = true;
    readFromFile();
}

SettingState::Data toSettingData(Settings::Parameter parameter) {
    switch (parameter) {
        case Settings::SoundVolume:
            return SettingState::Data::SoundVolume;
        case Settings::MusicVolume:
            return SettingState::Data::MusicVolume;
        case Settings::P1Left:
            return SettingState::Data::P1Left;
        case Settings::P1Right:
            return SettingState::Data::P1Right;
        case Settings::P1Up:
            return SettingState::Data::P1Up;
        case Settings::P1Down:
            return SettingState::Data::P1Down;
        case Settings::P2Left:
            return SettingState::Data::P2Left;
        case Settings::P2Right:
            return SettingState::Data::P2Right;
        case Settings::P2Up:
            return SettingState::Data::P2Up;
        case Settings::P2Down:
            return SettingState::Data::P2Down;
    }
}

std::string getData(std::vector<std::string>& data, Settings::Parameter type) {
    return SettingState::getData(data, toSettingData(type));
}

void Settings::readFromFile() {
    if (!SettingState::checkValidSettings(SettingState::mSettingsPath)) {
        SettingState::createDefaultData();
    }
    std::ifstream fin(SettingState::mSettingsPath);
    std::vector <std::string> dataList;
	dataList.clear();
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string word;
			fin >> word;
			dataList.push_back(word);
		}
	}
    fin.close();
    mSoundVolume = std::stof(getData(dataList, Settings::SoundVolume)) * 100;
    mMusicVolume = std::stof(getData(dataList, Settings::MusicVolume)) * 100;
    mKeyBinding[Player::PlayerOneMoveLeft] = stringToSFMLKey(getData(dataList, Settings::P1Left));
    mKeyBinding[Player::PlayerOneMoveRight] = stringToSFMLKey(getData(dataList, Settings::P1Right));
    mKeyBinding[Player::PlayerOneMoveUp] = stringToSFMLKey(getData(dataList, Settings::P1Up));
    mKeyBinding[Player::PlayerOneMoveDown] = stringToSFMLKey(getData(dataList, Settings::P1Down));
    mKeyBinding[Player::PlayerTwoMoveLeft] = stringToSFMLKey(getData(dataList, Settings::P2Left));
    mKeyBinding[Player::PlayerTwoMoveRight] = stringToSFMLKey(getData(dataList, Settings::P2Right));
    mKeyBinding[Player::PlayerTwoMoveUp] = stringToSFMLKey(getData(dataList, Settings::P2Up));
    mKeyBinding[Player::PlayerTwoMoveDown] = stringToSFMLKey(getData(dataList, Settings::P2Down));
}

void Settings::setPlayer(Player* player) {
    mPlayer = player;
    update();
}

void Settings::setMainSounds(SoundPlayer* sounds) {
    mMainSounds = sounds;
    update();
}

void Settings::setGameSounds(SoundPlayer* sounds) {
    mGameSounds = sounds;
    update();
}

void Settings::setMusicPlayer(MusicPlayer* musicPlayer) {
    mMusicPlayer = musicPlayer;
    update();
}

void Settings::update() {
    readFromFile();
    if (mPlayer != nullptr) {
        for (auto& pair : mKeyBinding) {
            mPlayer->assignKey(pair.first, pair.second);
        }
    }
    if (mMainSounds != nullptr) {
        mMainSounds->setVolume(mSoundVolume);
    }
    if (mGameSounds != nullptr) {
        mGameSounds->setVolume(mSoundVolume);
    }
    if (mMusicPlayer != nullptr) {
        mMusicPlayer->setVolume(mMusicVolume);
    }
}

void Settings::lazyUpdate() {
    if (SettingState::pendingUpdated()) {
        update();
    }
}

float Settings::getMusicVolume() {
    lazyUpdate();
    return mMusicVolume;
}

float Settings::getSoundVolume() {
    lazyUpdate();
    return mSoundVolume;
}