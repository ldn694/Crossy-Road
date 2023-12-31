#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>

class Rain {
    class RainDrop {
    private:
        float x, y;
        sf::RectangleShape shape;
    public:
        sf::Vector2f getPosition();
        RainDrop(float x, float y, float width, float height);
        void move(sf::Vector2f offset);
        void draw(sf::RenderWindow& window);
    };
private:
    std::vector<RainDrop> drops;
    float width, height;
    float dropWidth, dropHeight;
    float dropSpeed;
    sf::Time spawnTimer;
    sf::Time spawnPeriod;
    sf::Time startRainTimer;
    sf::Time startRainPeriod;
    sf::RectangleShape background;
public:
    Rain(float width, float height, float dropWidth, float dropHeight, float dropSpeed, sf::Time spawnPeriod, sf::Time startRainPeriod);
    void reset();
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);
};