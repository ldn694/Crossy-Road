#include "Settings.hpp"

Settings::Settings(Player* player) : mPlayer(player) {
    changed = true;
    mMusicVolume = 100;
    mSoundVolume = 100;
    mKeyBinding[Player::PlayerOneMoveLeft] = sf::Keyboard::A;
    mKeyBinding[Player::PlayerOneMoveRight] = sf::Keyboard::D;
    mKeyBinding[Player::PlayerOneMoveUp] = sf::Keyboard::W;
    mKeyBinding[Player::PlayerOneMoveDown] = sf::Keyboard::S;
    mKeyBinding[Player::PlayerTwoMoveLeft] = sf::Keyboard::Left;
    mKeyBinding[Player::PlayerTwoMoveRight] = sf::Keyboard::Right;
    mKeyBinding[Player::PlayerTwoMoveUp] = sf::Keyboard::Up;
    mKeyBinding[Player::PlayerTwoMoveDown] = sf::Keyboard::Down;
}

void Settings::setPlayer(Player* player) {
    mPlayer = player;
    update();
}

void Settings::setSoundPlayer(SoundPlayer* sounds) {
    mSounds = sounds;
    update();
}

void Settings::update() {
    if (mPlayer != nullptr) {
        for (auto& pair : mKeyBinding) {
            mPlayer->assignKey(pair.first, pair.second);
        }
    }
    if (mSounds != nullptr) {
        mSounds->setVolume(mSoundVolume);
    }
}

void Settings::lazyUpdate() {
    if (isChanged()) {
        update();
        flipChanged();
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

void Settings::flipChanged() {
    changed = !changed;
}

bool Settings::isChanged() const {
    return changed;
}