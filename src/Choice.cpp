#include "Choice.hpp"
#include "Utility.hpp"
#include <iostream>
#include <cassert>

Choice::Choice(ClickableList* mList, int id, Context context, Clickable::Info info): Clickable(mList, context, id, info.status) {
    isHovering = false;
    previousIsHovering = false;
    assertThrow(info.floatList.size() == 5, "Choice: floatList size must be 5");
    assertThrow(info.stringList.size() == 1, "Choice: stringList size must be 1");
    assertThrow(info.textureIDList.size() == 3, "Choice: textureIDList size must be 3");
    assertThrow(info.fontIDList.size() == 1, "Choice: fontIDList size must be 1");
    assertThrow(info.colorList.size() == 1, "Choice: colorList size must be 1");
    assertThrow(info.soundEffectIDList.size() == 2 || info.soundEffectIDList.size() == 0, "Choice: soundEffectIDList size must be 2 or 0");
    mRect = sf::FloatRect(info.floatList[0], info.floatList[1], info.floatList[2], info.floatList[3]);
    mTextureID[0] = info.textureIDList[0];
    mTextureID[1] = info.textureIDList[1];
    mTextureID[2] = info.textureIDList[2];
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

bool Choice::isInside(sf::Vector2f position) {
    return mRect.contains(position);
}

void Choice::draw() {
    if (mStatus.isClickable()){
        mSprite.setTexture(mContext.textures->get(isHovering ? mTextureID[1] : mTextureID[0]));
    } else {
        mSprite.setTexture(mContext.textures->get(mTextureID[2]));
    }
    setSize(mSprite, sf::Vector2f(mRect.width, mRect.height));
    mSprite.setPosition(mRect.left, mRect.top);
    mContext.window->draw(mSprite);
    mContext.window->draw(mText);
}

void Choice::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        previousIsHovering = isHovering;
        isHovering = isInside(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
        if (isHovering && !previousIsHovering && mStatus.isClickable()) {
            mContext.sounds->play(mSoundEffectID[0]);
        }
    }
    if (!mStatus.isClickable()) return;
    if (event.type == sf::Event::MouseButtonPressed) {
        if (isInside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            mContext.sounds->play(mSoundEffectID[1]);
            if (event.mouseButton.button == sf::Mouse::Left) {
                requestPushAnnouncement(Clickable::LeftPressed);
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                requestPushAnnouncement(Clickable::RightPressed);
            }
        }
    }
}

void Choice::update(sf::Time dt) {
   
}

sf::String Choice::getString() {
    return mText.getString();
}