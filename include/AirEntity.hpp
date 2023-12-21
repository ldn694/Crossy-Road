#pragma once
#include "Entity.hpp"

class AirEntity: public Entity{
public:
    virtual sf::FloatRect getHitbox() const;
};