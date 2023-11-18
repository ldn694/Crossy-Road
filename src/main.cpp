#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Resources/TextureHolder.hpp"
int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Crossy Road" };
    window.setFramerateLimit(144);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    TextureHolder mTextures;
    mTextures.load(Textures::Cat, "Assets/Images/cat.png");
    sf::Sprite sprite(mTextures.get(Textures::Cat));
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(window.getSize().x / 4.f, window.getSize().y / 4.f);
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}