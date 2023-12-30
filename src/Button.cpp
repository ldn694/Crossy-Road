#include "Button.hpp"
#include "Utility.hpp"
#include <iostream>
#include <cassert>

Button::Button(ClickableList* mList, int id, Context context, Clickable::Info info): Clickable(mList, context, id, info.status) {
    isHovering = false;
    assertThrow(info.floatList.size() == 5, "Button: floatList size must be 5");
    assertThrow(info.stringList.size() == 1, "Button: stringList size must be 1");
    assertThrow(info.textureIDList.size() == 2, "Button: textureIDList size must be 2");
    assertThrow(info.fontIDList.size() == 1, "Button: fontIDList size must be 1");
    assertThrow(info.colorList.size() == 1, "Button: colorList size must be 1");
    mRect = sf::FloatRect(info.floatList[0], info.floatList[1], info.floatList[2], info.floatList[3]);
    mTextureID[0] = info.textureIDList[0];
    mTextureID[1] = info.textureIDList[1];
    mText.setCharacterSize(info.floatList[4]);
    mText.setFont(context.fonts->get(info.fontIDList[0]));
    mText.setFillColor(info.colorList[0]);
    mText.setString(info.stringList[0]);
    centerOrigin(mText);
    mText.setPosition(mRect.left + mRect.width / 2.f, mRect.top + mRect.height / 2.f);
    mSprite.setTexture(mContext.textures->get(mTextureID[0]));
    mSprite.setPosition(info.floatList[0], info.floatList[1]);
    mSprite.setScale(mRect.width / mSprite.getLocalBounds().width, mRect.height / mSprite.getLocalBounds().height);
}

bool Button::isInside(sf::Vector2f position) {
    return mRect.contains(position);
}

void Button::setText(const std::string &newString)
{
    mText.setString(newString);
}

std::string Button::getText()
{
    std::string result = mText.getString();
    return result;
}

void Button::draw() {
    if (mStatus.isHoverable()) {
        mSprite.setTexture(mContext.textures->get(isHovering ? mTextureID[1] : mTextureID[0]));
    }
    else {
        mSprite.setTexture(mContext.textures->get(mTextureID[0]));
    }
    mContext.window->draw(mSprite);
    mContext.window->draw(mText);
}

void Button::handleEvent(const sf::Event& event) {
    if (!mStatus.isClickable()) return;
    if (event.type == sf::Event::MouseMoved) {
        isHovering = isInside(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (isInside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                requestPushAnnouncement(Clickable::LeftPressed);
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                requestPushAnnouncement(Clickable::RightPressed);
            }
        }
    }
}

void Button::update(sf::Time dt) {
   
}