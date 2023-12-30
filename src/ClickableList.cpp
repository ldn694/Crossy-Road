#include "ClickableList.hpp"
#include "Foreach.hpp"
#include <iostream>

#include <cassert>


ClickableList::ClickableList(Context context)
    : mClickables()
    , mContext(context)
    , mFactories()
{
}

void ClickableList::update(sf::Time dt)
{
    for (auto itr = mClickables.rbegin(); itr != mClickables.rend(); ++itr)
    {
        itr->second->update(dt);
    }
}

void ClickableList::draw()
{
    for (auto itr = mClickables.begin(); itr != mClickables.end(); ++itr)
    {
        itr->second->actualDraw();
    }
}

void ClickableList::handleEvent(const sf::Event& event)
{
    for (auto itr = mClickables.begin(); itr != mClickables.end(); ++itr)
    {
        itr->second->handleEvent(event);
    }
}

void ClickableList::pushAnnouncement(Clickable::Action action, int id)
{
    mAnnounceMents.push(Clickable::Announcement(action, id));
}

Clickable::Announcement ClickableList::popAnnouncement()
{
    Clickable::Announcement announcement = mAnnounceMents.front();
    mAnnounceMents.pop();
    return announcement;
}

bool ClickableList::pendingAnnouncement() const
{
    return !mAnnounceMents.empty();
}

void ClickableList::setClickable(int id, bool clickable)
{
    auto found = mClickables.find(id);
    assert(found != mClickables.end());

    found->second->setClickable(clickable);
}

void ClickableList::setDrawable(int id, bool drawable)
{
    auto found = mClickables.find(id);
    assert(found != mClickables.end());

    found->second->setDrawable(drawable);
}

void ClickableList::setHoverable(int id, bool hoverable)
{
    auto found = mClickables.find(id);
    assert(found != mClickables.end());

    found->second->setHoverable(hoverable);
}

void ClickableList::addClickable(Clickable::Type clickableType, int id, Clickable::Info info)
{
    mClickables.insert(std::make_pair(id, createClickable(clickableType, id, info)));
}

void ClickableList::setTextByID(int clickableID, const std::string& newString)
{
    auto found = mClickables.find(clickableID);
    if (found != mClickables.end()) {
         found->second->setText(newString);
    }
    return ;
}

std::string ClickableList::getTextByID(int clickableID)
{
    auto found = mClickables.find(clickableID);
    if (found != mClickables.end()) {
       return found->second->getText();
    }
    return std::string();
}





Clickable::Ptr ClickableList::createClickable(Clickable::Type clickableType, int id, Clickable::Info info)
{
    auto found = mFactories.find(clickableType);
    assert(found != mFactories.end());

    return found->second(id, info);
}