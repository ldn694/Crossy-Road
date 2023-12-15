#pragma once

#include "Category.hpp"
#include "Command.hpp"
#include "Foreach.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>
#include <iostream>


struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;


	public:
								SceneNode();

		void					attachChild(Ptr child);
		Ptr						detachChild(const SceneNode& node);
		
		void					update(sf::Time dt);

		sf::Vector2f			getWorldPosition() const;
		sf::Transform			getWorldTransform() const;

		void					onCommand(const Command& command, sf::Time dt);
		virtual unsigned int	getCategory() const;

		template <typename GameObject>
		std::vector <GameObject*>		findChildrenByCategory(Category::Type category);
		SceneNode*						getRoot();


	private:
		virtual void			updateCurrent(sf::Time dt);
		void					updateChildren(sf::Time dt);

		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		std::vector<Ptr>		mChildren;
		SceneNode*				mParent;
};

template <typename GameObject>
std::vector <GameObject*> SceneNode::findChildrenByCategory(Category::Type category)
{
	std::vector <GameObject*> result;
	if (category > 0 && getCategory() == category)
		result.push_back(derivedPtr<GameObject>(this));
	for (Ptr& child : mChildren)
	{
		std::vector <GameObject*> childResult = child.get()->findChildrenByCategory<GameObject>(category);
		result.insert(result.end(), childResult.begin(), childResult.end());
	}
	return result;
}