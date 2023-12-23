#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "Player.hpp"
#include "Scoreboard.hpp"

struct Context
{
                        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Scoreboard& scoreboard);

    sf::RenderWindow*	window;
    TextureHolder*		textures;
    FontHolder*			fonts;
    Scoreboard*         scoreboard;
    //Player*				player;
};