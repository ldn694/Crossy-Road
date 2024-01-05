#pragma once
#include "Clickable.hpp"
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.hpp"

class ClickableList;

class Button: public Clickable {
private:
    sf::FloatRect mRect;
    sf::Text mText;
    Textures::ID mTextureID[2];
    SoundEffect::ID mSoundEffectID[2];
    sf::Sprite mSprite;
    bool previousIsHovering, isHovering;
public:
    Button(ClickableList* mList, int id, Context context, Clickable::Info info);
    void draw();
    void handleEvent(const sf::Event& event);
    void update(sf::Time dt);
    bool isInside(sf::Vector2f position);
    sf::String getString();
};