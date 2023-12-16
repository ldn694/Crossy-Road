#pragma once
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>
#include <queue>


namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
		Notify
	};


public:
	explicit			StateStack(Context context);

	template <typename T>
	void				registerState(States::ID stateID);

	void				update(sf::Time dt);
	void				draw();
	void				handleEvent(const sf::Event& event);

	void				pushState(States::ID stateID, State::Info info = State::Info());
	void				popState();
	void				clearStates();
	void				notifyState(States::ID stateID, State::Info info);
	bool				pendingNotification(States::ID stateID);
	State::Info			popNotification(States::ID stateID);

	bool				isEmpty() const;


private:
	State::Ptr			createState(States::ID stateID, State::Info info);
	void				applyPendingChanges();


private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, States::ID stateID = States::None, State::Info info = State::Info());

		Action				action;
		States::ID			stateID;
		State::Info			info;
	};


private:
	std::vector<State::Ptr>										mStack;
	std::vector<PendingChange>									mPendingList;

	Context														mContext;
	std::map<States::ID, std::function<State::Ptr(State::Info)>>	mFactories;
	std::map<States::ID, std::queue<State::Info>>					mInfos;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this, stateID](State::Info info)
		{
			return State::Ptr(new T(*this, stateID, mContext, info));
		};
	mInfos[stateID] = std::queue<State::Info>();
}

