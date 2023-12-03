#include "Clickable.hpp"
#include "ClickableList.hpp"
#include <iostream>

ClickableStatus::ClickableStatus(bool isDrawable, bool isClickable, bool isHoverable): status(0) {
        status |= (isDrawable << 0);
        status |= (isClickable << 1);
        status |= (isHoverable << 2);
}

ClickableInfo::ClickableInfo(): status(ClickableStatus()), floatList(std::vector<float>()), stringList(std::vector<std::string>()), textureIDList(std::vector<Textures::ID>()), timeList(std::vector<sf::Time>()) {}

bool ClickableStatus::isDrawable() {
    return status & 1;
}

bool ClickableStatus::isClickable() {
    return status & 2;
}

bool ClickableStatus::isHoverable() {
    return status & 4;
} 

void ClickableStatus::setDrawable(bool drawable) {
    status = status & ~(drawable << 0) ^ (drawable << 0);
}

void ClickableStatus::setClickable(bool clickable) {
    status = status & ~(clickable << 1) ^ (clickable << 1);
}

void ClickableStatus::setHoverable(bool hoverable) {
    status = status & ~(hoverable << 2) ^ (hoverable << 2);
}

Clickable::Announcement::Announcement(Clickable::Action action, int id): action(action), id(id) {}

Clickable::Clickable(ClickableList* list, Context context, int id, ClickableStatus status): mID(id), mStatus(status), mContext(context), mList(list) {}

void Clickable::actualDraw() {
    if (mStatus.isDrawable()) {
        draw();
    }
}

void Clickable::setDrawable(bool drawable) {
    mStatus.setDrawable(drawable);
}

void Clickable::setClickable(bool clickable) {
    mStatus.setClickable(clickable);
}

void Clickable::setHoverable(bool hoverable) {
    mStatus.setHoverable(hoverable);
}

void Clickable::requestPushAnnouncement(Clickable::Action action) {
    mList->pushAnnouncement(action, mID);
}


