#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Context.hpp"

struct ClickableStatus {
    int status;
    ClickableStatus(bool isDrawable = 0, bool isClickable = 0, bool isHoverable = 0);
    bool isDrawable();
    bool isClickable();
    bool isHoverable();
    void setDrawable(bool drawable);
    void setClickable(bool clickable);
    void setHoverable(bool hoverable);
};

struct ClickableInfo {
    std::vector <float>             floatList;
    std::vector <std::string>       stringList;
    std::vector <Textures::ID>      textureIDList;
    std::vector <Fonts::ID>         fontIDList;
    std::vector <sf::Vector2f>      vector2fList;
    std::vector <sf::Time>          timeList;
    std::vector <sf::Color>         colorList;
    ClickableStatus                 status;
    ClickableInfo();
};

class ClickableList;

class Clickable {
private:
protected:
    int                 mID;
    ClickableStatus     mStatus;
    Context             mContext;
    ClickableList*      mList;
    virtual void        draw() = 0;
public:
    enum Type {
        Button
    };
    enum Action {
        LeftClick,
        RightClick
    };
    struct Announcement {
        Clickable::Action               action;
        int                             id;
        Announcement(Clickable::Action action, int id);
    };
	typedef std::unique_ptr<Clickable> Ptr;
                    Clickable(ClickableList* list, Context context, int id, ClickableStatus status);
    void            actualDraw();
    virtual void    handleEvent(const sf::Event& event) = 0;
    virtual void    update(sf::Time dt) = 0;
    virtual bool    isInside(sf::Vector2f position) = 0;
    void            setDrawable(bool drawable);
    void            setClickable(bool clickable);
    void            setHoverable(bool hoverable);
    void            requestPushAnnouncement(Clickable::Action action);
};