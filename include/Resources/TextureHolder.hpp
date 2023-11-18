#include "ResourceHolder.hpp"

// namespace sf
// {
// 	class Texture;
// }

namespace Textures
{
	enum ID
	{
		Cat,
        Dog,
        Chicken
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;