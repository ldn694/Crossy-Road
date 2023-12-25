#include "Rain.hpp"
#include <iostream>

sf::Vector2f Rain::RainDrop::getPosition() {
    return shape.getPosition();
}

Rain::RainDrop::RainDrop(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color(255, 255, 255, 200));
}

void Rain::RainDrop::move(sf::Vector2f offset) {
    shape.move(offset);
}

void Rain::RainDrop::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

Rain::Rain(float width, float height, float dropWidth, float dropHeight, float dropSpeed, sf::Time spawnPeriod, sf::Time startRainPeriod) {
    this->width = width;
    this->height = height;
    this->dropWidth = dropWidth;
    this->dropHeight = dropHeight;
    this->dropSpeed = dropSpeed;
    this->spawnPeriod = spawnPeriod;
    this->startRainPeriod = startRainPeriod;
    background.setSize(sf::Vector2f(width, height));
    background.setPosition(sf::Vector2f(0, 0));
}

void Rain::update(sf::Time dt) {
    if (startRainTimer < startRainPeriod) {
        startRainTimer += dt;
        startRainTimer = std::min(startRainTimer, startRainPeriod);
    }
    background.setFillColor(sf::Color(0, 0, 0, 100 * startRainTimer.asSeconds() / startRainPeriod.asSeconds()));
    spawnTimer += dt;
    if (spawnTimer >= spawnPeriod) {
        for (int i = 0; i < rand() % 30 + 1; i++) {
            drops.push_back(RainDrop(rand() % 1050, -dropHeight, dropWidth, dropHeight));
        }
        spawnTimer = sf::Time::Zero;
    }
    for (int i = 0; i < drops.size(); i++) {
        drops[i].move(sf::Vector2f(0, dropSpeed * dt.asSeconds()));
    }
    while (true) {
        int index = -1;
        for (int i = 0; i < drops.size(); i++) {
            if (drops[i].getPosition().y > 800) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            break;
        }
        else {
            drops.erase(drops.begin() + index);
        }
    }
}

void Rain::draw(sf::RenderWindow& window) {
    window.draw(background);
    for (int i = 0; i < drops.size(); i++) {
        drops[i].draw(window);
    }
}

void Rain::reset() {
    drops.clear();
    spawnTimer = sf::Time::Zero;
}