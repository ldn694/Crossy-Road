#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Context.hpp"

class ClickableList;

class Clickable {
public:
    enum Type {
        Button,
        Slide,
        Choice,
        TypeBox,
    };
    enum Action {
        LeftPressed,
        RightPressed,
        LeftReleased,
        RightReleased,
        Moved
    };
    struct Status {
        int status;
        Status(bool isDrawable = 0, bool isClickable = 0, bool isHoverable = 0);
        bool isDrawable();
        bool isClickable();
        bool isHoverable();
        void setDrawable(bool drawable);
        void setClickable(bool clickable);
        void setHoverable(bool hoverable);
    };
    struct Info {
        std::vector <float>             floatList;
        std::vector <std::string>       stringList;
        std::vector <Textures::ID>      textureIDList;
        std::vector <Fonts::ID>         fontIDList;
        std::vector <sf::Vector2f>      vector2fList;
        std::vector <sf::Time>          timeList;
        std::vector <sf::Color>         colorList;
        Status                 status;
        Info();
    };
    struct Announcement {
        Action               action;
        int                             id;
        Announcement(Action action, int id);
    };
private:
protected:
    int                 mID;
    Status              mStatus;
    Context             mContext;
    ClickableList*      mList;
    virtual void        draw() = 0;
public:
	typedef std::unique_ptr<Clickable> Ptr;
                    Clickable(ClickableList* list, Context context, int id, Status status);
    void            actualDraw();
    virtual void    handleEvent(const sf::Event& event) = 0;
    virtual void    update(sf::Time dt) = 0;
    virtual bool    isInside(sf::Vector2f position) = 0;
    virtual sf::String getString() = 0;
    void            setDrawable(bool drawable);
    void            setClickable(bool clickable);
    void            setHoverable(bool hoverable);
    void            requestPushAnnouncement(Clickable::Action action);
};