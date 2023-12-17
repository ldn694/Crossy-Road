#pragma once

#include <map>
#include "SceneNode.hpp"


struct Animation;

class FakeEntity;

class Entity : public SceneNode
{
	public:
		enum CollisionType {
			NoCollision,
			BlockedCollision,
			DeathCollision,
			NumCollisionTypes
		};
	public:
									Entity();
		void						setVelocity(sf::Vector2f velocity);
		void						setVelocity(float vx, float vy);
		void						accelerate(sf::Vector2f velocity);
		void						accelerate(float vx, float vy);
		sf::Vector2f				getVelocity() const;
		bool			    		pendingAnimation();
		void						addStaticAnimation(sf::Vector2f goalGlobalPosition, sf::Time duration);
		void						addDynamicAnimation(Entity* goalEntity, sf::Time duration, sf::Vector2f offset = sf::Vector2f(0, 0));
		CollisionType				handleCollision();
		void 						removeAnimation();
		virtual sf::FloatRect		getHitbox() const = 0;
									~Entity();


	private:
		Animation*					curAnimation = nullptr;
		FakeEntity*					mOriginNode = nullptr;
		virtual void				updateCurrent(sf::Time dt);
		void 						setOriginNode();
		void						resetOriginNode();

	

	private:
		sf::Vector2f		mVelocity;
		sf::Vector2f		mHitboxSize;
};
