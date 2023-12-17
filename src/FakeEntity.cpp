#include "FakeEntity.hpp"

FakeEntity::FakeEntity(Entity* owner) : mOwner(owner)
{
}

unsigned int FakeEntity::getCategory() const
{
    return Category::FakeEntity;
}

Entity* FakeEntity::getOwner()
{
    return mOwner;
}

sf::FloatRect FakeEntity::getHitbox() const
{
    return mOwner->getHitbox();
}