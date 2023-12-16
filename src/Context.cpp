#include "Context.hpp"
Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
: window(&window)
, textures(&textures)
, fonts(&fonts)
{
}