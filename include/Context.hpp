#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "Player.hpp"
#include "Scoreboard.hpp"

struct Context
{
                        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,sf::Music &backgroundmusic, Scoreboard& scoreboard);

    sf::RenderWindow*	window;
    TextureHolder*		textures;
    FontHolder*			fonts;
    Scoreboard*         scoreboard;
    Player*				player;
    sf::Music*          backgroundmusic;
};