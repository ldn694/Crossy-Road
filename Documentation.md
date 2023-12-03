# ResourceHolder

## Description

We use this class to hold different types of resources. It is a template class, so you can use it with any type of resource. Detailed information about the ResourceHolder class can be found in the [ResourceHolder.hpp](include\ResourceHolder.hpp) file.

## Public Methods

| Method | Description |
| ------ | ----------- |
| `ResourceHolder()` | Default constructor. |
| `~ResourceHolder()` | Default destructor. |
| `void load(const std::string& id, const std::string& filename)` | Loads a resource from a file. |
| `template <typename Parameter> void load(const std::string& id, const std::string& filename, const Parameter& secondParam)` | Loads a resource from a file with a second parameter. |
| `Resource& get(const std::string& id)` | Returns a reference to a resource. |
| `const Resource& get(const std::string& id) const` | Returns a const reference to a resource. |

## Usage

There are 2 pre-implemented ResoureHolder classes in the project: `TextureHolder` and `FontHolder`. It is recommneded to read [ResourceIdentifiers.hpp](include\ResourceIdentifiers.hpp) file for detailed information. In case you want to use the ResourceHolder class with a different type of resource, adding new images to `Images` folder or new fonts to `Fonts` folder, etc, please edit the [ResourceIdentifiers.hpp](include\ResourceIdentifiers.hpp) file.

## Example

### TextureHolder.hpp

Please refer to the [ResourceIdentifiers.hpp](include\ResourceIdentifiers.hpp) file for detailed information.

Here is a simple way to use the TextureHolder class:

```cpp
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
...
TextureHolder textures;
textures.load(Textures::ID::Button, "Assets/Images/Button.png"); // Loads a texture from a file. Please fix the path.
...
sf::Sprite sprite;
sprite.setTexture(textures.get(Textures::ID::Button)); // Sets the texture of the sprite.
...
```

### FontHolder.hpp

Please refer to the [ResourceIdentifiers.hpp](include\ResourceIdentifiers.hpp) file for detailed information.

Here is a simple way to use the FontHolder class:

```cpp
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
...
FontHolder fonts;
fonts.load(Fonts::ID::Main, "Assets/Fonts/Main.ttf"); // Loads a font from a file. Please fix the path.
...
sf::Text text;
text.setFont(fonts.get(Fonts::ID::Main)); // Sets the font of the text.
...
```

# Clickable and ClickableList

## Description

There will be multiple objects that need mouse interaction handling. We use the `Clickable` class as an interface for these objects. Detailed information about the `Clickable` class can be found in the [Clickable.hpp](include\Clickable.hpp) file.

Instead of direct interaction with `Clickable` objects, we use `ClickableList` class as an **Observer** to handle the click events. Detailed information about the `ClickableList` class can be found in the [ClickableList.hpp](include\ClickableList.hpp) file.

## Usage

### ClickableStatus

`ClickableStatus` struct is used to store the status of a `Clickable` object. It consists of 3 boolean variables: `isClickable`, `isHoverable` and `isPressable`. 
* `isDrawable` is used to determine whether the object is drawable or not. If not, the object will not be drawn, however, it will can be clickable.
* `isClickable` is used to determine whether the object is clickable or not. If not, the object will not be clickable, however, it can still be drawn.
* `isHoverable` is used to determine whether the object is hoverable or not. If not, the object will not be hoverable, however, it can still be clickable and drawn.

### Clickable

For each object that needs mouse interaction handling, we create a class that inherits from the `Clickable` class. We will need to overwrite the following methods:

* `bool isInside(sf::Vector2f mousePosition) const` - Returns true if the mouse position is inside the object.
* `void draw()` - Draws the object.
* `void handleEvent(const sf::Event &event)` - Handles the events.
* `void update(sf::Time dt)` - Updates the object.

### ClickableList

`ClickableList` class is used to handle the click events. It is an **Observer** class. Each derived of `State` class should contain a `ClickableList` object. The `ClickableList` object will handle the click events for all `Clickable` objects in that state. Each `State` class should call the following methods of `ClickableList` in the according methods of `State` class:

* `void handleEvent(const sf::Event &event)` - Handles the events.
* `void update(sf::Time dt)` - Updates the objects.
* `void draw()` - Draws the objects.

### Create a new Clickable object

We use Factory Method design pattern to create new `Clickable` objects. In each derived class of `State` class (e.g. `MenuState`), we first need to register the type of `Clickable` objects (e.g. `Button`) that we will use in that state. Then, we can create new `Clickable` objects using the Factory Method `addClickable()`.

About the `ClickableInfo` struct: It is used to store the information about the `Clickable` object. `ClickableInfo` consists of multiple `std::vector` of different types. Each `std::vector` stores the information about a specific property of the `Clickable` object. For example, `floatList` stores the information about the position and size of the `Clickable` object; `status` stores the information about the status of the `Clickable` object. 

Below is an example of creating a two new `Button` object - a derived of `Clickable` class:

```cpp
    mClickableList.registerClickable<Button>(Clickable::Type::Button); //do this only once in the constructor of the derived class of State class
    ...
	ClickableInfo info;
	info.floatList = { 0, 0, 100, 100, 10 };
	info.stringList = { "Button 0" };
	info.status = ClickableStatus(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::Button, Textures::PressedButton };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, 0, info);
    ...
    info.floatList = {500, 200, 70, 70, 10};
	info.status = ClickableStatus(true, true, true);
	info.textureIDList = { Textures::Button, Textures::PressedButton };
	info.stringList = { "Button 1" };
	info.fontIDList = { Fonts::Main };
	info.colorList = { sf::Color::Black };
	mClickableList.addClickable(Clickable::Type::Button, 1, info);
```

### Handle the click events

`Clickablelist` stores a `std::queue` of `Clickable::Announcement` objects. Each `Clickable::Announcement` object stores the information about the click event. The `ClickableList` class will handle the click events for all `Clickable` objects in that state. For example, if the user clicks on a `Clickable` object, `ClickableList` will be notified and it will store the information about the click event in the `std::queue`.

Below is an example of handling the click events:

```cpp
//In the handleEvent() method of the derived class of State class
mClickableList.handleEvent(event);
while (mClickableList.pendingAnnouncement()) {
    Clickable::Announcement announcement = mClickableList.popAnnouncement();
    if (announcement.action == Clickable::LeftClick) {
        std::cout << "Left Clicked " << announcement.id << "\n";
    }
    else if (announcement.action == Clickable::RightClick) {
        std::cout << "Right Clicked " << announcement.id << "\n";
    }
}
```

## Clickable Objects

### Button

`Button` is a derived class of `Clickable` class. It is a simple button that can be clicked. It has 2 textures: normal texture and pressed texture. It also has a text on it. If you hover over the button, the texture will be set to the pressed texture.

To create a new `Button` object, we need to provide the following information:
| Information | Required number of elements | Description |
| ----------- | --------------------------- | ----------- |
| `floatList` | 5 | The first 4 elements are respectively the left, top, width and height of the button. The last element is the character size of the text. |
| `stringList` | 1 | The text on the button. |
| `status` | 1 | The status of the button. |
| `fontIDList` | 1 | The font of the text. |
| `textureIDList` | 2 | The normal texture and pressed texture's ID of the button. |
| `colorList` | 1 | The color of the text. |


Detailed information about the `Button` class can be found in the [Button.hpp](include\Button.hpp) file.






