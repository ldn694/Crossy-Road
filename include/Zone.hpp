#pragma once

#include "Entity.hpp"

class Road;

class Zone : public Entity{
public:
    enum Safety {
        Safe,
        Unsafe
    };
    Zone(Safety safety, sf::FloatRect hitbox, Road* road);
    ~Zone();
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect getHitbox() const;
    Safety getSafety() const;
    virtual unsigned int	getCategory() const;
    Road* getRoad();
private:
    Road* mRoad;
    sf::FloatRect mHitbox;
    Safety mSafety;
};