#include "Entity.hpp"
#include "Utility.hpp"
#include "Animation.hpp"
#include <iostream>

Entity::Entity(sf::Vector2f hitboxSize): mVelocity(0.f, 0.f), mHitboxSize(hitboxSize) {}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

void Entity::updateCurrent(sf::Time dt)
{
	if (pendingAnimation()) {
		sf::Vector2f animationOffset = curAnimation->getAnimationOffset(this, dt);
		move(mVelocity * dt.asSeconds() + animationOffset);
		if (curAnimation->elapsedTime >= curAnimation->duration) {
			removeAnimation();
		}
	}
	else {
		move(mVelocity * dt.asSeconds());
	}
}

bool Entity::pendingAnimation()
{
	return curAnimation != nullptr;
}

void Entity::removeAnimation()
{
	delete curAnimation;
	curAnimation = nullptr;
}

void Entity::addStaticAnimation(sf::Vector2f goalGlobalPosition, sf::Time duration) {
	if (pendingAnimation()) {
		return;
	}
	curAnimation = new StaticAnimation(goalGlobalPosition, duration);
}

void Entity::addDynamicAnimation(Entity* goalEntity, sf::Time duration, sf::Vector2f offset) {
	if (pendingAnimation()) {
		return;
	}
	curAnimation = new DynamicAnimation(goalEntity, duration, offset);
}

Entity::~Entity() {
	if (pendingAnimation()) {
		removeAnimation();
	}
}