#pragma once

#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "Context.hpp"
#include "ClickableList.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Info {
		std::vector <float>             floatList;
		std::vector <std::string>       stringList;
		std::vector <Textures::ID>      textureIDList;
		std::vector <Fonts::ID>         fontIDList;
		std::vector <sf::Vector2f>      vector2fList;
		std::vector <sf::Time>          timeList;
		std::vector <sf::Color>         colorList;
		Info();
	};


public:
	State(StateStack& stack, States::ID stateID, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;


protected:
	void				requestStackPush(States::ID stateID, State::Info info = State::Info());
	void				requestStackPop();
	void				requestStateClear();
	void				requestNotifyState(States::ID stateID, State::Info info);
	bool 			  	pendingNotification();
	State::Info 		popNotification();

	Context				getContext() const;


private:
	StateStack* mStack;
	Context				mContext;
	States::ID			mStateID;
};
