#pragma once
#include "Entity.hpp"

class FakeEntity: public Entity {
private:
    Entity*              mOwner;
public:
                            FakeEntity(Entity* owner);
    virtual unsigned int    getCategory() const;
    sf::FloatRect           getHitbox() const;
    Entity*                 getOwner(); 
};