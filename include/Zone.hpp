#pragma once

#include "Entity.hpp"

class Zone : public Entity{
public:
    enum Safety {
        Safe,
        Unsafe
    };
    Zone(Safety safety, sf::FloatRect hitbox);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect getHitbox() const;
    Safety getSafety() const;
private:
    sf::FloatRect mHitbox;
    Safety mSafety;
};