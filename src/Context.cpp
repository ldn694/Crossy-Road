#include "Context.hpp"
Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Scoreboard& scoreboard)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, scoreboard(&scoreboard)
{
}