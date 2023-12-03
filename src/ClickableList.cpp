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

void ClickableList::addClickable(Clickable::Type clickableType, int id, ClickableInfo info)
{
    mClickables.insert(std::make_pair(id, createClickable(clickableType, id, info)));
}

Clickable::Ptr ClickableList::createClickable(Clickable::Type clickableType, int id, ClickableInfo info)
{
    auto found = mFactories.find(clickableType);
    assert(found != mFactories.end());

    return found->second(id, info);
}