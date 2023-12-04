#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "Player.hpp"

struct Context
{
                        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

    sf::RenderWindow*	window;
    TextureHolder*		textures;
    FontHolder*			fonts;
    Player*				player;
};