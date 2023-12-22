#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class ScrollBar{
    public:
                                  ScrollBar();
                                  ScrollBar(float x, float y, float width,sf::RenderWindow &window,float z);
    void                          update(sf::RenderWindow& window);
    void                          draw(sf::RenderWindow& window);
    float                         getValue() const;
    void                          handleEvent(const sf::Event& event,sf::RenderWindow &window);
    private:
    sf::RectangleShape bar;
    sf::RectangleShape slider;
    sf::RectangleShape updateBar;
    bool isDragging;
};