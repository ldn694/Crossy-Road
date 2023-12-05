#include "StateStack.hpp"
#include "Foreach.hpp"
#include "Utility.hpp"

#include <cassert>
#include <iostream>


StateStack::StateStack(Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{
}

void StateStack::update(sf::Time dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	// Draw all active states from bottom to top
	FOREACH(State::Ptr& state, mStack)
		state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID, State::Info info)
{
	mPendingList.push_back(PendingChange(Push, stateID, info));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop, States::None));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear, States::None));
}

void StateStack::notifyState(States::ID stateID, State::Info info)
{
	mPendingList.push_back(PendingChange(Notify, stateID, info));
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

bool StateStack::pendingNotification(States::ID stateID)
{
	return !mInfos[stateID].empty();
}

State::Info StateStack::popNotification(States::ID stateID)
{
	assertThrow(!mInfos[stateID].empty(), "No pending notifications for state " + toString(stateID));
	State::Info info = mInfos[stateID].front();
	mInfos[stateID].pop();
	return info;
}

State::Ptr StateStack::createState(States::ID stateID, State::Info info)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second(info);
}

void StateStack::applyPendingChanges()
{
	FOREACH(PendingChange change, mPendingList)
	{
		switch (change.action)
		{
			case Push:
				mStack.push_back(createState(change.stateID, change.info));
				break;

			case Pop:
				mStack.pop_back();
				break;

			case Clear:
				mStack.clear();
				break;

			case Notify:
				mInfos[change.stateID].push(change.info);
				break;
		}
	}

	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID, State::Info info) {
	this->action = action;
	this->stateID = stateID;
	this->info = info;
}
