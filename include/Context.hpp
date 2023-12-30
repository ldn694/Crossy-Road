#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "Settings.hpp"
#include "Scoreboard.hpp"
#include "SoundPlayer.hpp"

struct Context
{
                        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, SoundPlayer& sounds, Scoreboard& scoreboard, Settings& settings);

    sf::RenderWindow*	window;
    TextureHolder*		textures;
    SoundPlayer*		sounds;
    FontHolder*			fonts;
    Scoreboard*         scoreboard;
    Settings*           settings;
    //Player*				player;
};