#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include "Entity.hpp"

struct Animation {
protected:
	void updateTime(sf::Time dt);
public:
	sf::Time duration;
	sf::Time elapsedTime;
	Animation(sf::Time duration);
	virtual sf::Vector2f getAnimationStep(Entity* startEntity, sf::Time dt) = 0;
    ~Animation() {}
};

struct StaticAnimation: Animation {
	sf::Vector2f goalGlobalPosition;
	StaticAnimation(sf::Vector2f goalGlobalPosition, sf::Time duration);
	sf::Vector2f getAnimationStep(Entity* startEntity, sf::Time dt);
};

struct DynamicAnimation: Animation {
	Entity* goalEntity;
	sf::Vector2f offset;
	DynamicAnimation(Entity* goalEntity, sf::Time duration, sf::Vector2f offset = sf::Vector2f(0, 0));
	sf::Vector2f getAnimationStep(Entity* startEntity, sf::Time dt);
};