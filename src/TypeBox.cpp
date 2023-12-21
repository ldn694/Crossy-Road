#include "TypeBox.hpp"
#include "Utility.hpp"
#include <iostream>
#include <cassert>

TypeBox::TypeBox(ClickableList* mList, int id, Context context, Clickable::Info info): Clickable(mList, context, id, info.status) {
    isHovering = false;
    assertThrow(info.floatList.size() == 7, "TypeBox: floatList size must be 7");
    assertThrow(info.stringList.size() == 1, "TypeBox: stringList size must be 1");
    assertThrow(info.textureIDList.size() == 3, "TypeBox: textureIDList size must be 3");
    assertThrow(info.fontIDList.size() == 2, "TypeBox: fontIDList size must be 2");
    assertThrow(info.colorList.size() == 2, "TypeBox: colorList size must be 2");

    mRect = sf::FloatRect(info.floatList[0], info.floatList[1], info.floatList[2], info.floatList[3]);

    ratio = info.floatList[4];
    mBox = sf::FloatRect(info.floatList[0] + info.floatList[2]*ratio, info.floatList[1] + info.floatList[3]* ratio, info.floatList[2] * (1.0 - 2.0*ratio) , info.floatList[3] * (1.0 - 2.0*ratio));

    mCursor.setSize(sf::Vector2f(2, info.floatList[6]));
    mCursor.setFillColor(sf::Color::White);
    mCursor.setOrigin(mCursor.getSize().x / 2.f, mCursor.getSize().y / 2.f);

    mTextureID[0] = info.textureIDList[0];
    mTextureID[1] = info.textureIDList[1];
    mTextureID[2] = info.textureIDList[2];

    mPlayerName = info.stringList[0];
    mShowText.setCharacterSize(info.floatList[5]);
    mShowText.setFont(context.fonts->get(info.fontIDList[0]));
    mShowText.setFillColor(info.colorList[0]);
    mShowText.setString(mPlayerName);
    centerOrigin(mShowText);
    mShowText.setPosition(mRect.left + mRect.width / 2.f, mRect.top + mRect.height / 2.f);

    mInputText.setCharacterSize(info.floatList[6]);
    mInputText.setFont(context.fonts->get(info.fontIDList[1]));
    mInputText.setFillColor(info.colorList[1]);
    centerOrigin(mInputText);
    mInputText.setPosition(mRect.left + mRect.width / 2.f, mRect.top + mRect.height / 2.f);

    mSprite.setTexture(mContext.textures->get(mTextureID[0]));
    mSprite.setPosition(info.floatList[0], info.floatList[1]);
    mSprite.setScale(mRect.width / mSprite.getLocalBounds().width, mRect.height / mSprite.getLocalBounds().height);

    mSpriteInput.setTexture(mContext.textures->get(mTextureID[2]));
    mSpriteInput.setPosition(info.floatList[0] + info.floatList[2]*ratio, info.floatList[1] + info.floatList[3]*ratio);
    mSpriteInput.setScale(mBox.width / mSpriteInput.getLocalBounds().width, mBox.height / mSpriteInput.getLocalBounds().height);

}

bool TypeBox::isInside(sf::Vector2f position) {
    return mRect.contains(position);
}

void TypeBox::draw() {
    if (mStatus.isClickable()){
        //std::cerr << "TypeBox: " << mID << " is not available to input" << std::endl;
        mSprite.setTexture(mContext.textures->get(isHovering ? mTextureID[1] : mTextureID[0]));

        mShowText.setString(mPlayerName);
        centerOrigin(mShowText);
        mShowText.setPosition(mRect.left + mRect.width / 2.f, mRect.top + mRect.height / 2.f);

        mContext.window->draw(mSprite);
        mContext.window->draw(mShowText);
    } else {
        //std::cerr << "TypeBox: " << mID << " is available to input" << std::endl;
        mSprite.setTexture(mContext.textures->get(mTextureID[0]));

        mInputText.setString(mString);
        centerOrigin(mInputText);
        mInputText.setPosition(mRect.left + mRect.width / 2.f, mRect.top + mRect.height / 2.f);
        //set cursor beside the text
        mCursor.setPosition(mInputText.getPosition().x + mInputText.getLocalBounds().width / 2.f + 5, mInputText.getPosition().y);
        
        mContext.window->draw(mSprite);
        mContext.window->draw(mSpriteInput);
        mContext.window->draw(mInputText);
        mContext.window->draw(mCursor);
    }
}

void TypeBox::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        isHovering = isInside(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
    }
    if (event.type == sf::Event::TextEntered) {
        if (mStatus.isClickable()) return;
        if (event.text.unicode == 8) {
            if (mString.getSize() > 0) {
                mString.erase(mString.getSize() - 1, 1);
            }
            isShowCursor = true;
            mClock.restart();
            mCursor.setFillColor(sf::Color::White);
        }
        else if (event.text.unicode == 13) {
            if (mString.getSize() != 0) mPlayerName = mString;
            mString.clear();
            mStatus.setClickable(true);
        }
        else if ((event.text.unicode >= 65 && event.text.unicode <= 90) || (event.text.unicode >= 48 && event.text.unicode <= 57) || (event.text.unicode >= 97 && event.text.unicode <= 122) && mString.getSize() < LimitOfName) {
            mString += event.text.unicode;
            std::cerr << "TypeBox: " << mID << " input: " << mString.toAnsiString() << std::endl;
            isShowCursor = true;
            mClock.restart();
            mCursor.setFillColor(sf::Color::White);
        }
    }
    if (!mStatus.isClickable()) return;
    if (event.type == sf::Event::MouseButtonPressed) {
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

void TypeBox::update(sf::Time dt) {
    if (mStatus.isClickable()) return;
    if (mClock.getElapsedTime().asSeconds() > 0.5) {
        isShowCursor = !isShowCursor;
        mClock.restart();
    }
    if (isShowCursor) {
        mCursor.setFillColor(sf::Color::White);
    }
    else {
        mCursor.setFillColor(sf::Color::Transparent);
    }
}