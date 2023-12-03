#pragma once
#include <map>
#include <vector>
#include <queue>
#include "Clickable.hpp"
#include "State.hpp"
#include "Context.hpp"

class ClickableList
{
public:
    explicit			        ClickableList(Context context);

    template <typename T>
    void				        registerClickable(Clickable::Type clickableType);

    void				        update(sf::Time dt);
    void				        draw();
    void				        handleEvent(const sf::Event& event);

    void                        pushAnnouncement(Clickable::Action action, int id);
    Clickable::Announcement		popAnnouncement();
    bool				        pendingAnnouncement() const;


    void                        addClickable(Clickable::Type clickableType, int id, ClickableInfo info);


private:
    Clickable::Ptr		        createClickable(Clickable::Type clickableType, int id, ClickableInfo info);


private:
    Context										                                    mContext;
    std::map<Clickable::Type, std::function<Clickable::Ptr(int, ClickableInfo)>>	mFactories;
    std::map<int, std::unique_ptr<Clickable>>                                       mClickables;
    std::queue<Clickable::Announcement>                                             mAnnounceMents;
};


template <typename T>
void ClickableList::registerClickable(Clickable::Type clickableType)
{
    mFactories[clickableType] = [this](int id, ClickableInfo info)
        {
            return Clickable::Ptr(new T(this, id, mContext, info));
        };
}

