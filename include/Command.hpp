#pragma once

#include "Category.hpp"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>
#include <memory>


class SceneNode;

struct Command
{
												Command();

	std::function<void(SceneNode&, sf::Time)>	action;
	unsigned int								category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=] (SceneNode& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

template <typename GameObject>
GameObject* derivedPtr(SceneNode* node)
{
	assert(node != nullptr);

	// Check if cast is safe
	assert(dynamic_cast<GameObject*>(node) != nullptr);

	return static_cast<GameObject*>(node);
}
