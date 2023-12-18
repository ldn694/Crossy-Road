#include "Animation.hpp"
#include "Entity.hpp"
#include <iostream>

Animation::Animation(sf::Time duration) : duration(duration), elapsedTime(sf::Time::Zero) {
}

void Animation::updateTime(sf::Time dt) {
	elapsedTime += dt;
}

StaticAnimation::StaticAnimation(sf::Vector2f offset, sf::Time duration) : Animation(duration), offset(offset) {}

sf::Vector2f StaticAnimation::getAnimationStep(Entity* startEntity, sf::Time dt) {
	dt = std::min(dt, duration - elapsedTime);
	sf::Vector2f resOffset = offset / (duration - elapsedTime).asSeconds() * dt.asSeconds();
	offset -= resOffset;
	updateTime(dt);
	return resOffset;
}


DynamicAnimation::DynamicAnimation(Entity* goalEntity, sf::Time duration, sf::Vector2f offset) : Animation(duration), goalEntity(goalEntity), offset(offset) {
}

sf::Vector2f DynamicAnimation::getAnimationStep(Entity* startEntity, sf::Time dt) {
	sf::Vector2f startGlobalPosition = startEntity->getWorldPosition();
	sf::Vector2f goalGlobalPosition = goalEntity->getWorldPosition() + offset;
	sf::Vector2f dynamicOffset = goalGlobalPosition - startGlobalPosition;
	dt = std::min(dt, duration - elapsedTime);
	sf::Vector2f resOffset = dynamicOffset / (duration - elapsedTime).asSeconds() * dt.asSeconds();
	updateTime(dt);
	return resOffset;
}