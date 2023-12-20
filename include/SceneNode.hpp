#pragma once

#include "Category.hpp"
#include "Command.hpp"
#include "Foreach.hpp"
#include "Utility.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>
#include <iostream>
#include <queue>


struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;


	public:
									SceneNode();
		virtual						~SceneNode();
		void				    	detachChildren();
		void						attachChildren();
		void						requestDetach(SceneNode* node);
		void						requestAttach(Ptr child);
		void						filterEmptyChildren();
		friend void					switchParent(SceneNode* child, SceneNode* newParent);
		
		void					update(sf::Time dt);

		sf::Vector2f			getWorldPosition() const;
		sf::Transform			getWorldTransform() const;

		void					onCommand(const Command& command, sf::Time dt);
		virtual unsigned int	getCategory() const;

		template <typename GameObject>
		std::vector <GameObject*>		findChildrenByCategory(Category::Type category);
		template <typename GameObject>
		std::vector <GameObject*>		findDirectChildrenByCategory(Category::Type category);
		SceneNode*						getRoot();
		SceneNode*						getParent();
		int						countChildren() const;


	private:
		Ptr						detachChild(const SceneNode& node);
		void					attachChild(Ptr child);

		virtual void			updateCurrent(sf::Time dt);
		void					updateChildren(sf::Time dt);

		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
		std::unique_ptr<SceneNode>& findDirectChild(SceneNode* child);


	private:
		std::vector<Ptr>									mChildren;
		SceneNode*											mParent;
		std::queue <SceneNode*>								mDetachQueue;
		std::queue <SceneNode::Ptr> 						mAttachQueue;
};

template <typename GameObject>
std::vector <GameObject*> SceneNode::findChildrenByCategory(Category::Type category)
{
	filterEmptyChildren();
	std::vector <GameObject*> result;
	if (category > 0 && getCategory() & category)
		result.push_back(derivedPtr<GameObject>(this));
	for (Ptr& child : mChildren)
	{
		assertThrow(child.get() != nullptr, "child is nullptr");
		std::vector <GameObject*> childResult = child.get()->findChildrenByCategory<GameObject>(category);
		result.insert(result.end(), childResult.begin(), childResult.end());
	}
	return result;
}

template <typename GameObject>
std::vector <GameObject*> SceneNode::findDirectChildrenByCategory(Category::Type category)
{
	filterEmptyChildren();
	std::vector <GameObject*> result;
	for (Ptr& child : mChildren)
	{
		if (category > 0 && child->getCategory() & category)
			result.push_back(derivedPtr<GameObject>(child.get()));
	}
	return result;
}