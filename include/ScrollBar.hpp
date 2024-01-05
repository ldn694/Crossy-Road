#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
class ScrollBar{
    public:
                                  ScrollBar();
                                  ScrollBar(float x, float y, float width,float z);
    void                          update(sf::RenderWindow& window);
    void                          draw(sf::RenderWindow& window);
    float                         getValue() const;
    bool                          handleEvent(const sf::Event& event,sf::RenderWindow &window);
    float                         getPos() const;
    void                          updateBarSize();
    private:
    sf::RectangleShape bar;
    sf::RectangleShape slider;
    sf::RectangleShape updateBar;
    bool isDragging;
    int id;
};