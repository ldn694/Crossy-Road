#include "SceneNode.hpp"
#include "Command.hpp"
#include "Foreach.hpp"
#include "Utility.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>


SceneNode::SceneNode()
	: mChildren()
	, mParent(nullptr)
{
}

SceneNode::~SceneNode()
{
	
}

void SceneNode::filterEmptyChildren()
{
	while (true) {
		std::vector <Ptr>::iterator found = mChildren.end();
		for (int i = 0; i < mChildren.size(); i++) {
			if (mChildren[i].get() == nullptr) {
				found = mChildren.begin() + i;
				break;
			}
		}
		if (found != mChildren.end()) {
			mChildren.erase(found);
		}
		else {
			break;
		}
	}
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

void SceneNode::attachChildAtFront(Ptr child)
{
	child->mParent = this;
	mChildren.insert(mChildren.begin(), std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	filterEmptyChildren();
	detachChildren();
	attachChildren();
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
	FOREACH(Ptr & child, mChildren) {
		if (child.get()) {
			child->update(dt);
		}
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	FOREACH(const Ptr & child, mChildren)
		if (child.get()) {
			child->draw(target, states);
		}
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent) {
		transform = node->getTransform() * transform;
	}

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	// Command current node, if category matches
	if (command.category & getCategory()) {
		command.action(*this, dt);
	}
	filterEmptyChildren();
	// Command children
	FOREACH(Ptr & child, mChildren) {
		if (child.get()) {
			child->onCommand(command, dt);
		}
	}
}

void SceneNode::requestDetach(SceneNode* node)
{
	mDetachQueue.push(node);
}

void SceneNode::requestAttachAtFront(Ptr child)
{
	mAttachQueueAtFront.push(std::move(child));
}

void SceneNode::detachChildren()
{
	filterEmptyChildren();
	while (!mDetachQueue.empty()) {
		SceneNode* child = mDetachQueue.front();
		mDetachQueue.pop();
		detachChild(*child);
	}
}

void SceneNode::requestAttach(Ptr child)
{
	mAttachQueue.push(std::move(child));
}

void SceneNode::attachChildren()
{
	while (!mAttachQueue.empty()) {
		Ptr child = std::move(mAttachQueue.front());
		mAttachQueue.pop();
		attachChild(std::move(child));
	}
	while (!mAttachQueueAtFront.empty()) {
		Ptr child = std::move(mAttachQueueAtFront.front());
		mAttachQueueAtFront.pop();
		attachChildAtFront(std::move(child));
	}
}

std::unique_ptr<SceneNode>& SceneNode::findDirectChild(SceneNode* child)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == child; });
	assert(found != mChildren.end());
	return *found;
}

void switchParent(SceneNode* child, SceneNode* newParent)
{
	SceneNode* oldParent = child->getParent();
	assertThrow(newParent != nullptr, "newParent is nullptr");
	if (oldParent == newParent)
		return;
	if (oldParent == nullptr) {
		SceneNode::Ptr childPtr(child);
		newParent->requestAttach(std::move(childPtr));
		newParent->attachChildren();
		return;
	}
	std::unique_ptr<SceneNode>& childPtr = oldParent->findDirectChild(child);
	childPtr.release();
	std::unique_ptr<SceneNode> childPtrCopy(child);
	// oldParent->requestDetach(child);
	newParent->requestAttach(std::move(childPtrCopy));
	newParent->attachChildren();
}

SceneNode* SceneNode::getParent()
{
	return mParent;
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

SceneNode* SceneNode::getRoot()
{
	if (mParent == nullptr)
		return this;
	else
		return mParent->getRoot();
}

int SceneNode::countChildren() const
{
	int res = mChildren.size();
	FOREACH(const Ptr & child, mChildren) {
		if (child.get()) {
			res += child->countChildren();
		}
	}
	return res;
}