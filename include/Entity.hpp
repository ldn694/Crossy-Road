#pragma once

#include <map>
#include "SceneNode.hpp"

struct Animation;

class Entity : public SceneNode
{
	public:
		void						setVelocity(sf::Vector2f velocity);
		void						setVelocity(float vx, float vy);
		void						accelerate(sf::Vector2f velocity);
		void						accelerate(float vx, float vy);
		sf::Vector2f				getVelocity() const;
		bool			    		pendingAnimation();
		void						addStaticAnimation(sf::Vector2f goalGlobalPosition, sf::Time duration);
		void						addDynamicAnimation(Entity* goalEntity, sf::Time duration, sf::Vector2f offset = sf::Vector2f(0, 0));
		void 						removeAnimation();
									~Entity();


	private:
		Animation*					curAnimation = nullptr;
		virtual void				updateCurrent(sf::Time dt);


	private:
		sf::Vector2f		mVelocity;
};
