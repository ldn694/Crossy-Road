#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ScrollBar.hpp"

class ScrollBarList {
public:
    ScrollBarList();
    ScrollBarList(std::string path);
    void                      draw(sf::RenderWindow& window);
    bool                      handleEvent(const sf::Event& event, sf::RenderWindow& window);
    float                     getVolumeSound() const;
    float                     getVolumeMusic() const;
    void                      toggleSound();
    void                      toggleMusic();
private:
    void                      updateFile();
private:
    std::vector<ScrollBar>   mScrollBars;
    std::string              mFileName;
};