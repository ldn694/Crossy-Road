#include "Clickable.hpp"
#include "ClickableList.hpp"
#include <iostream>

Clickable::Status::Status(bool isDrawable, bool isClickable, bool isHoverable): status() {
    setDrawable(isDrawable);
    setClickable(isClickable);
    setHoverable(isHoverable);
}

Clickable::Info::Info(): status() {}

bool Clickable::Status::isDrawable() {
    return status & 1;
}

bool Clickable::Status::isClickable() {
    return status & 2;
}

bool Clickable::Status::isHoverable() {
    return status & 4;
} 

void Clickable::Status::setDrawable(bool drawable) {
    status = status & ~(drawable << 0) ^ (drawable << 0);
}

void Clickable::Status::setClickable(bool clickable) {
    status = status & ~(clickable << 1) ^ (clickable << 1);
}

void Clickable::Status::setHoverable(bool hoverable) {
    status = status & ~(hoverable << 2) ^ (hoverable << 2);
}

Clickable::Announcement::Announcement(Clickable::Action action, int id): action(action), id(id) {}

Clickable::Clickable(ClickableList* list, Context context, int id, Status status): mID(id), mStatus(status), mContext(context), mList(list) {}

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


