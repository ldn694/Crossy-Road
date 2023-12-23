#include "Context.hpp"
Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,sf::Music &backgroundmusic,float &mVolume)
: window(&window)
, textures(&textures)
, fonts(&fonts)
,backgroundmusic(&backgroundmusic)
,mVolume(&mVolume)
{
}