#pragma once

#include "Player.hpp"
#include "SoundPlayer.hpp"

#include <SFML/Window/Event.hpp>
#include <map>

class Settings {
private:
    float mMusicVolume;
    float mSoundVolume = 100.f;
    std::map <Player::Action, sf::Keyboard::Key> mKeyBinding;
    bool changed = true;
    Player* mPlayer;
    SoundPlayer* mSounds;
    void update();
    void flipChanged();
public:
    Settings(Player* player = nullptr);
    void setPlayer(Player* player);
    void setSoundPlayer(SoundPlayer* sounds);
    float getMusicVolume();
    float getSoundVolume();
    bool isChanged() const;
    void lazyUpdate();
};