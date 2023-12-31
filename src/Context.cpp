#include "Context.hpp"
Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,sf::Music &backgroundmusic, Scoreboard& scoreboard)
: window(&window)
, textures(&textures)
, fonts(&fonts)
,backgroundmusic(&backgroundmusic)
, scoreboard(&scoreboard)
{
}