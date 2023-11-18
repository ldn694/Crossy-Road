# ResourceHolder

## Description

We use this class to hold different types of resources. It is a template class, so you can use it with any type of resource.

## Public Methods

| Method | Description |
| ------ | ----------- |
| `ResourceHolder()` | Default constructor. |
| `~ResourceHolder()` | Default destructor. |
| `void load(const std::string& id, const std::string& filename)` | Loads a resource from a file. |
| `template <typename Parameter> void load(const std::string& id, const std::string& filename, const Parameter& secondParam)` | Loads a resource from a file with a second parameter. |
| `Resource& get(const std::string& id)` | Returns a reference to a resource. |
| `const Resource& get(const std::string& id) const` | Returns a const reference to a resource. |

## Example

### TextureHolder.hpp

Please refer to the [TextureHolder.hpp](include/Resources/TextureHolder.hpp) file for detailed information.

Here is a simple way to use the TextureHolder class:

```cpp
#include "TextureHolder.hpp" //Fix the path to the header file
sf::Texture texture;
texture.loadFromFile("texture.png");
sf::Sprite sprite(texture);
...
window.draw(sprite);
```
