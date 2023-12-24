#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ScrollBar.hpp"

class ScrollBarList {
    public:
                              ScrollBarList();
    void                      draw(sf::RenderWindow &window);
    void                      handleEvent(const sf::Event& event,sf::RenderWindow &window);
    float                     getVolumeSound() const;
    float                     getVolumeMusic() const;
    private:
     std::vector<ScrollBar>   mScrollBars;
};