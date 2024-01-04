#include "Context.hpp"
Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, SoundPlayer& sounds, MusicPlayer& music, Scoreboard& scoreboard, Settings& settings)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, sounds(&sounds)
, music(&music)
, scoreboard(&scoreboard)
, settings(&settings)
{
}