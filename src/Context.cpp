#include "Context.hpp"
Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, SoundPlayer& sounds, Scoreboard& scoreboard, Settings& settings)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, sounds(&sounds)
, scoreboard(&scoreboard)
, settings(&settings)
{
}