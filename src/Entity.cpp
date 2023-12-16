#include "Entity.hpp"
#include "Utility.hpp"
#include "Animation.hpp"
#include "GameStatus.hpp"
#include <iostream>

Entity::Entity() : mVelocity(0.f, 0.f)
{
	mOriginPosition = getWorldPosition();
}

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

Entity::CollisionType Entity::handleCollision()
{
	auto mCategory = getCategory();
	if (!(mCategory & (Category::Hostile | Category::Obstacle | Category::Player))) {
		return CollisionType::NoCollision;
	}
	if (mCategory & Category::Player) {
		auto root = getRoot();
		auto hostiles = root->findChildrenByCategory<Entity>(Category::Hostile);
		for (auto hostile : hostiles) {
			if (intersection(getHitbox(), hostile->getHitbox()) > 0 && hostile != this) {
				return CollisionType::DeathCollision;
			}
		}
		auto obstacles = root->findChildrenByCategory<Entity>(Category::Obstacle);
		for (auto obstacle : obstacles) {
			if (intersection(getHitbox(), obstacle->getHitbox()) > 0 && obstacle != this) {
				return CollisionType::BlockedCollision;
			}
		}
		return CollisionType::NoCollision;
	}
	if (mCategory & Category::Hostile) {
		auto root = getRoot();
		auto player = root->findChildrenByCategory<Entity>(Category::Player)[0];
		if (intersection(getHitbox(), player->getHitbox()) > 0) {
			return CollisionType::DeathCollision;
		}
		return CollisionType::NoCollision;
	}
	if (mCategory & Category::Obstacle) {
		auto root = getRoot();
		auto player = root->findChildrenByCategory<Entity>(Category::Player)[0];
		if (intersection(getHitbox(), player->getHitbox()) > 0) {
			return CollisionType::BlockedCollision;
		}
		return CollisionType::NoCollision;
	}
}

void Entity::updateCurrent(sf::Time dt)
{
	if (pendingAnimation()) {
		sf::Vector2f animationOffset = curAnimation->getAnimationOffset(this, dt);
		move(mVelocity * dt.asSeconds() + animationOffset);
		auto collisionType = handleCollision();
		if (collisionType == CollisionType::DeathCollision) {
			throw GameStatus::GAME_LOST;
		}
		else if (collisionType == CollisionType::BlockedCollision) {
			move(-mVelocity * dt.asSeconds() - animationOffset);
			sf::Time duration = curAnimation->duration - curAnimation->elapsedTime;
			removeAnimation();
			addStaticAnimation(mOriginPosition, duration);
		}
		if (curAnimation->elapsedTime >= curAnimation->duration) {
			removeAnimation();
		}
	}
	else {
		mOriginPosition = getWorldPosition();
		move(mVelocity * dt.asSeconds());
		auto collisionType = handleCollision();
		if (collisionType == CollisionType::DeathCollision) {
			throw GameStatus::GAME_LOST;
		}
		else if (collisionType == CollisionType::BlockedCollision) {
			move(-mVelocity * dt.asSeconds());
		}
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
	std::cout << "Added new static animation\n";
	std::cout << "Goal position: " << goalGlobalPosition.x << " " << goalGlobalPosition.y << "\n";
	curAnimation = new StaticAnimation(goalGlobalPosition, duration);
	mOriginPosition = getWorldPosition();
}

void Entity::addDynamicAnimation(Entity* goalEntity, sf::Time duration, sf::Vector2f offset) {
	if (pendingAnimation()) {
		return;
	}
	curAnimation = new DynamicAnimation(goalEntity, duration, offset);
	mOriginPosition = getWorldPosition();
}

Entity::~Entity() {
	if (pendingAnimation()) {
		removeAnimation();
	}
}