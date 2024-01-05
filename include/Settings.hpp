#pragma once

#include "Player.hpp"
#include "SoundPlayer.hpp"
#include "MusicPlayer.hpp"

#include <SFML/Window/Event.hpp>
#include <map>

class Settings {
public:
    enum Parameter {
        SoundVolume,
        MusicVolume,
        P1Left,
        P1Right,
        P1Up,
        P1Down,
        P2Left,
        P2Right,
        P2Up,
        P2Down,
    };
private:
    float mMusicVolume = 100.f;
    float mSoundVolume = 100.f;
    std::map <Player::Action, sf::Keyboard::Key> mKeyBinding;
    bool changed = true;
    Player* mPlayer;
    SoundPlayer *mMainSounds;
    SoundPlayer *mGameSounds;
    MusicPlayer *mMusicPlayer;
    void update();
public:
    Settings(Player* player = nullptr);
    void readFromFile();
    void setPlayer(Player* player);
    void setMainSounds(SoundPlayer* sounds);
    void setGameSounds(SoundPlayer* sounds);
    void setMusicPlayer(MusicPlayer* musicPlayer);
    float getMusicVolume();
    float getSoundVolume();
    void lazyUpdate();
};