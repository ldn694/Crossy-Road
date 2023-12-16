#include "State.hpp"
#include "StateStack.hpp"

State::Info::Info() {}

State::State(StateStack& stack, States::ID stateID, Context context)
	: mStack(&stack)
	, mContext(context)
	, mStateID(stateID) {}

State::~State()
{
}

void State::requestStackPush(States::ID stateID, State::Info info)
{
	mStack->pushState(stateID, info);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

void State::requestNotifyState(States::ID stateID, State::Info info)
{
	mStack->notifyState(stateID, info);
}

bool State::pendingNotification()
{
	return mStack->pendingNotification(mStateID);
}

State::Info State::popNotification()
{
	return mStack->popNotification(mStateID);
}

Context State::getContext() const
{
	return mContext;
}
