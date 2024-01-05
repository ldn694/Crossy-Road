#pragma once
#include <map>
#include <vector>
#include <queue>
#include "Clickable.hpp"
#include "State.hpp"
#include "Context.hpp"
#include "Button.hpp"

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

    void                        setClickable(int id, bool clickable);
    void                        setDrawable(int id, bool drawable);
    void                        setHoverable(int id, bool hoverable);
    sf::String                  getString(int id);


    void                        addClickable(Clickable::Type clickableType, int id, Clickable::Info info);
    void                        setTextByID(int clickableID,const std::string &newString);
    std::string                 getTextByID(int clickableID); 


private:
    Clickable::Ptr		        createClickable(Clickable::Type clickableType, int id, Clickable::Info info);


private:
    Context										                                    mContext;
    std::map<Clickable::Type, std::function<Clickable::Ptr(int, Clickable::Info)>>	mFactories;
    std::map<int, std::unique_ptr<Clickable>>                                       mClickables;
    std::queue<Clickable::Announcement>                                             mAnnounceMents;
};


template <typename T>
void ClickableList::registerClickable(Clickable::Type clickableType)
{
    mFactories[clickableType] = [this](int id, Clickable::Info info)
        {
            return Clickable::Ptr(new T(this, id, mContext, info));
        };
}