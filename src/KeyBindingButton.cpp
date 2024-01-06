#include "KeyBindingButton.hpp"
#include "Utility.hpp"
#include <iostream>
#include <cassert>

KeyBindingButton::KeyBindingButton(ClickableList* mList, int id, Context context, Clickable::Info info) : Clickable(mList, context, id, info.status) {
    isHovering = false;
    previousIsHovering = false;
    isPressed = false;
    assertThrow(info.floatList.size() == 5, "KeyBindingButton: floatList size must be 5");
    assertThrow(info.stringList.size() == 1, "KeyBindingButton: stringList size must be 1");
    assertThrow(info.textureIDList.size() == 3, "KeyBindingButton: textureIDList size must be 3");
    assertThrow(info.fontIDList.size() == 1, "KeyBindingButton: fontIDList size must be 1");
    assertThrow(info.colorList.size() == 1, "KeyBindingButton: colorList size must be 1");
    assertThrow(info.soundEffectIDList.size() == 2 || info.soundEffectIDList.size() == 0, "KeyBindingButton: soundEffectIDList size must be 2 or 0");
    mRect = sf::FloatRect(info.floatList[0], info.floatList[1], info.floatList[2], info.floatList[3]);
    for (int i = 0; i < 3; i++) {
        mTextureID[i] = info.textureIDList[i];
    }
    if (info.soundEffectIDList.size() == 2) {
        mSoundEffectID[0] = info.soundEffectIDList[0];
        mSoundEffectID[1] = info.soundEffectIDList[1];
    }
    else {
        mSoundEffectID[0] = SoundEffect::Mouse_Hover;
        mSoundEffectID[1] = SoundEffect::Mouse_Click;
    }
    mText.setCharacterSize(info.floatList[4]);
    mText.setFont(context.fonts->get(info.fontIDList[0]));
    mText.setFillColor(info.colorList[0]);
    mText.setString(info.stringList[0]);
    centerOrigin(mText);
    mText.setPosition(mRect.left + mRect.width / 2.f, mRect.top + mRect.height / 2.f);
    mSprite.setTexture(mContext.textures->get(mTextureID[0]));
    mSprite.setPosition(info.floatList[0], info.floatList[1]);
    setSize(mSprite, sf::Vector2f(mRect.width, mRect.height));
}

bool KeyBindingButton::isInside(sf::Vector2f position) {
    return mRect.contains(position);
}

void KeyBindingButton::setText(const std::string &newString)
{
    mText.setString(newString);
    centerOrigin(mText);
}

std::string KeyBindingButton::getText()
{
    std::string result = mText.getString();
    return result;
}

void KeyBindingButton::draw() {
    if (isPressed) {
        mSprite.setTexture(mContext.textures->get(mTextureID[2]));
    }
    else if (mStatus.isHoverable()) {
            mSprite.setTexture(mContext.textures->get(isHovering ? mTextureID[1] : mTextureID[0]));
    }
    else {
        mSprite.setTexture(mContext.textures->get(mTextureID[0]));
    }
    setSize(mSprite, sf::Vector2f(mRect.width, mRect.height));
    mSprite.setPosition(mRect.left, mRect.top);
    mContext.window->draw(mSprite);
    mContext.window->draw(mText);
}

void KeyBindingButton::handleEvent(const sf::Event& event) {
    if (!mStatus.isClickable()) return;
    if (event.type == sf::Event::MouseMoved) {
        if (isHovering && !previousIsHovering) {
            previousIsHovering = isHovering;
            mContext.sounds->play(mSoundEffectID[0]);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (isInside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            mContext.sounds->play(mSoundEffectID[1]);
            if (event.mouseButton.button == sf::Mouse::Left) {
                requestPushAnnouncement(Clickable::LeftPressed);
                if (!isPressed) {
                    isPressed = true;
                    requestPushAnnouncement(Clickable::Toggled);
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                requestPushAnnouncement(Clickable::RightPressed);
            }
        }
        else {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (isPressed) {
                    isPressed = false;
                    requestPushAnnouncement(Clickable::Toggled);
                }
            }
        }
    }
}

void KeyBindingButton::update(sf::Time dt) {
    previousIsHovering = isHovering;
    isHovering = isInside(sf::Vector2f(sf::Mouse::getPosition(*mContext.window)));
}
sf::String KeyBindingButton::getString() {
    return mText.getString();
}