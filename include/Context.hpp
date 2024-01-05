#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "Settings.hpp"
#include "Scoreboard.hpp"
#include "SoundPlayer.hpp"
#include "MusicPlayer.hpp"

struct Context
{
                        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, SoundPlayer& sounds, MusicPlayer& music, Scoreboard& scoreboard, Settings& settings);

    sf::RenderWindow*	window;
    TextureHolder*		textures;
    SoundPlayer*		sounds;
    FontHolder*			fonts;
    Scoreboard*         scoreboard;
    MusicPlayer*        music;
    Settings*           settings;
    //Player*				player;
};