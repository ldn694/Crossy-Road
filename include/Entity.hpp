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
		struct CollisionInfo {
			CollisionType type;
			Entity* mover;
			Entity* blocker;
			CollisionInfo(CollisionType type, Entity* mover, Entity* blocker);
		};
	public:
									Entity();
		void						setVelocity(sf::Vector2f velocity);
		void						setVelocity(float vx, float vy);
		void						accelerate(sf::Vector2f velocity);
		void						accelerate(float vx, float vy);
		sf::Vector2f				getVelocity() const;
		bool			    		pendingAnimation();
		bool						isFakeAnimation(); //return true if current animation is a fake animation
		bool						addStaticAnimation(sf::Vector2f goalGlobalPosition, sf::Time duration);
		bool						addDynamicAnimation(Entity* goalEntity, sf::Time duration, sf::Vector2f offset = sf::Vector2f(0, 0));
		CollisionInfo				handleCollision();
		void 						removeAnimation();
		virtual sf::FloatRect		getHitbox() const = 0;
		CollisionInfo				getCollisionInfo() const;
									~Entity();


	private:
		Animation*					curAnimation = nullptr;
		bool						isMovingBack = false;
		FakeEntity*					mOriginNode = nullptr;
		CollisionInfo				mCollisionInfo = CollisionInfo(NoCollision, nullptr, nullptr);
		void 						setOriginNode();
		void						resetOriginNode();
		void 						announceGameLost(CollisionInfo info);
		
	protected:
		virtual void				updateCurrent(sf::Time dt);
	

	private:
		sf::Vector2f		mVelocity;
		sf::Vector2f		mHitboxSize;
};
