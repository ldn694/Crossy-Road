#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "ScrollBar.hpp"

ScrollBar::ScrollBar()
{
    std::cout<<"ScrollBar::default constructor"<<std::endl;
}

ScrollBar::ScrollBar(float x, float y, float width,float z)
 {
        bar.setSize(sf::Vector2f(width, 20.f));
        bar.setPosition(x, y);
        bar.setFillColor(sf::Color(200, 200, 200));

        slider.setSize(sf::Vector2f(20.f, 20.f));
        slider.setPosition(z, y);
        slider.setFillColor(sf::Color(100, 100, 100));
        
        updateBar.setSize(sf::Vector2f(z-x, 20.f));
        updateBar.setPosition(x, y);
        updateBar.setFillColor(sf::Color(100, 100, 100));
        isDragging = false;
         
    }
void ScrollBar::update(sf::RenderWindow &window)
 {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if (isDragging)
         {
            // Move the slider with the mouse
            slider.setPosition(mousePos.x - slider.getSize().x / 2, slider.getPosition().y);
            // Ensure the slider stays within the bounds of the bar
            if (slider.getPosition().x < bar.getPosition().x)
                slider.setPosition(bar.getPosition().x, slider.getPosition().y);
            if (slider.getPosition().x + slider.getSize().x > bar.getPosition().x + bar.getSize().x)
                slider.setPosition(bar.getPosition().x + bar.getSize().x - slider.getSize().x, slider.getPosition().y);
            float diff = slider.getPosition().x - 30.f;
            updateBar.setSize(sf::Vector2f(diff,20.f));
            updateBar.setPosition(bar.getPosition().x,bar.getPosition().y);
            updateBar.setFillColor(sf::Color(100,100,100));
         }
         
        // Handle mouse press/release events
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (bar.getGlobalBounds().contains(mousePos)) {
                isDragging = true;
            }
        } else {
            isDragging = false;
        }
    }
void ScrollBar::draw(sf::RenderWindow& window)
{
        window.draw(bar);
        window.draw(slider);
        window.draw(updateBar);
}
 float ScrollBar::getValue() const
{
        // Normalize the slider position to a value between 0 and 1
        return (slider.getPosition().x - bar.getPosition().x) / (bar.getSize().x - slider.getSize().x);
}

void ScrollBar::handleEvent(const sf::Event& event,sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Handle left mouse button press
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if (slider.getGlobalBounds().contains(mousePos)) {
            isDragging = true;
        }
    } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        // Handle left mouse button release
        isDragging = false;
    } else if (event.type == sf::Event::MouseMoved) {
        // Handle mouse movement
        if (isDragging) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            // Update the slider position based on the mouse movement
            slider.setPosition(mousePos.x - slider.getSize().x / 2, slider.getPosition().y);
            //std::cout<<slider.getPosition().x<<std::endl;
            // Ensure the slider stays within the bounds of the bar
            if (slider.getPosition().x < bar.getPosition().x)
                slider.setPosition(bar.getPosition().x, slider.getPosition().y);
            if (slider.getPosition().x + slider.getSize().x > bar.getPosition().x + bar.getSize().x)
                slider.setPosition(bar.getPosition().x + bar.getSize().x - slider.getSize().x, slider.getPosition().y);
            float diff = slider.getPosition().x - bar.getPosition().x;
           //std::cout<<diff<<std::endl;
            updateBar.setSize(sf::Vector2f(diff,20.f));
            updateBar.setPosition(bar.getPosition().x,bar.getPosition().y);
            updateBar.setFillColor(sf::Color(100,100,100));
            // save to text file
           // std::string filename = "Assets/Files/ScrollBar" + std::to_string(this->id) + ".txt";
            //std::cout<<std::to_string(this->id)<<std::endl;
           // std::ofstream fout(filename,std::ios::trunc);
           // fout<<slider.getPosition().x;
            //fout.close();
        }
    }
}

float ScrollBar::getPos() const
{
    return slider.getPosition().x;
}



