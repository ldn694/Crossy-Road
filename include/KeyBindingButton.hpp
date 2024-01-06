#pragma once
#include "Clickable.hpp"
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.hpp"
#include <iostream>
#include <string>
class ClickableList;

class KeyBindingButton: public Clickable {
private:
    sf::FloatRect mRect;
    sf::Text mText;
    Textures::ID mTextureID[3];
    SoundEffect::ID mSoundEffectID[2];
    sf::Sprite mSprite;
    bool previousIsHovering, isHovering;
    bool isPressed;
public:
    KeyBindingButton(ClickableList* mList, int id, Context context, Clickable::Info info);
    void draw();
    void handleEvent(const sf::Event& event);
    void update(sf::Time dt);
    bool isInside(sf::Vector2f position);
    void setText(const std::string &newString);
    std::string getText();
    sf::String getString();
};