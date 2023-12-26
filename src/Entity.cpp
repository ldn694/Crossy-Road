#include "Entity.hpp"
#include "Utility.hpp"
#include "Animation.hpp"
#include "GameStatus.hpp"
#include "FakeEntity.hpp"
#include <iostream>
#include <vector>

Entity::Entity() : mVelocity(0.f, 0.f)
{
	mOriginNode = nullptr;
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
				// std::cerr << "blocked by " << fromCategoryToString(obstacle->getCategory()) << "\n";
				return CollisionType::BlockedCollision;
			}
		}
		auto players = root->findChildrenByCategory<Entity>(Category::Player);
		for (auto player : players) {
			if (intersection(getHitbox(), player->getHitbox()) > 0 && player != this) {
				return CollisionType::BlockedCollision;
			}
		}
		return CollisionType::NoCollision;
	}
	if (mCategory & Category::Hostile) {
		auto root = getRoot();
		auto players = root->findChildrenByCategory<Entity>(Category::Player);
		if (players.empty()) return CollisionType::NoCollision;
		auto player = players[0];
		if (intersection(getHitbox(), player->getHitbox()) > 0) {
			return CollisionType::DeathCollision;
		}
		auto obstacles = root->findChildrenByCategory<Entity>(Category::Obstacle);
		for (auto obstacle : obstacles) {
			if (intersection(getHitbox(), obstacle->getHitbox()) > 0 && obstacle != this) {
				return CollisionType::BlockedCollision;
			}
		}
		return CollisionType::NoCollision;
	}
	if (mCategory & Category::Obstacle) {
		auto root = getRoot();
		auto players = root->findChildrenByCategory<Entity>(Category::Player);
		if (players.empty()) return CollisionType::NoCollision;
		auto player = players[0];
		if (intersection(getHitbox(), player->getHitbox()) > 0) {
			return CollisionType::BlockedCollision;
		}
		auto hostiles = root->findChildrenByCategory<Entity>(Category::Hostile);
		for (auto hostile : hostiles) {
			if (intersection(getHitbox(), hostile->getHitbox()) > 0 && hostile != this) {
				return CollisionType::BlockedCollision;
			}
		}
		return CollisionType::NoCollision;
	}
	return CollisionType::NoCollision;
}

bool Entity::isFakeAnimation()
{
	return mOriginNode != nullptr;
}

void Entity::updateCurrent(sf::Time dt)
{
	if (pendingAnimation()) {
		auto animationStep = curAnimation->getAnimationStep(this, dt);
		move(mVelocity * dt.asSeconds() + animationStep);
		CollisionType collisionType = CollisionType::NoCollision;
		if (!isMovingBack) {
			collisionType = handleCollision();
		}
		if (collisionType == CollisionType::DeathCollision) {
			throw GameStatus::GAME_LOST;
		}
		else if (collisionType == CollisionType::BlockedCollision) {
			move(-mVelocity * dt.asSeconds() - animationStep);
			sf::Time duration = curAnimation->elapsedTime;
			removeAnimation();
			isMovingBack = true;
			SceneNode* parent = getParent();
			auto fakeEntities = parent->findDirectChildrenByCategory<Entity>(Category::FakeEntity);
			Entity* thisFakeEntity = nullptr;
			for (auto fakeEntity : fakeEntities) {
				if (static_cast<FakeEntity*>(fakeEntity)->getOwner() == this) {
					thisFakeEntity = fakeEntity;
					break;
				}
			}
			addDynamicAnimation(thisFakeEntity, duration);
		}
		if (curAnimation->elapsedTime >= curAnimation->duration) {
			resetOriginNode();
			removeAnimation();
		}
	}
	else {
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
	isMovingBack = false;
}

void Entity::resetOriginNode() {
	if (mOriginNode != nullptr) {
		SceneNode* parent = mOriginNode->getParent();
		parent->requestDetach(mOriginNode);
		mOriginNode = nullptr;
	}
}

void Entity::setOriginNode() {
	resetOriginNode();
	std::unique_ptr<FakeEntity> originNode(new FakeEntity(this));
	mOriginNode = originNode.get();
	SceneNode* parent = getParent();
	parent->requestAttach(std::move(originNode));
	mOriginNode->setPosition(getPosition());
}

bool Entity::addStaticAnimation(sf::Vector2f goalGlobalPosition, sf::Time duration) {
	if (pendingAnimation()) {
		return false;
	}
	curAnimation = new StaticAnimation(goalGlobalPosition, duration);
	setOriginNode();
	return true;
}

bool Entity::addDynamicAnimation(Entity* goalEntity, sf::Time duration, sf::Vector2f offset) {
	if (pendingAnimation()) {
		return false;
	}
	curAnimation = new DynamicAnimation(goalEntity, duration, offset);
	if (!(goalEntity->getCategory() & Category::FakeEntity)) {
		setOriginNode();
	}
	else {

	}
	return true;
}

Entity::~Entity() {
	if (pendingAnimation()) {
		removeAnimation();
	}
}