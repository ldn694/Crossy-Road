#pragma once
#include "Clickable.hpp"
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.hpp"

class ClickableList;

class TypeBox : public Clickable {
private:
    sf::FloatRect mRect, mBox;
    sf::Text mShowText, mInputText;
    sf::String mString, mPlayerName;
    Textures::ID mTextureID[3];
    sf::Sprite mSprite, mSpriteInput;
    sf::RectangleShape mCursor;
    sf::Clock mClock;
    bool isShowCursor;
    bool isHovering;
    double ratio = 1.0/6;
    int LimitOfName = 9;
public:
    TypeBox(ClickableList* mList, int id, Context context, Clickable::Info info);
    void draw();
    void handleEvent(const sf::Event& event);
    void update(sf::Time dt);
    sf::String getString();
    bool isInside(sf::Vector2f position);
};