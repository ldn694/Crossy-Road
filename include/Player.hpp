#pragma once

#include "Command.hpp"

#include <SFML/Window/Event.hpp>

#include <map>


class CommandQueue;

class Player
{
	public:
		enum Action
		{
			PlayerOneMoveLeft,
			PlayerOneMoveRight,
			PlayerOneMoveUp,
			PlayerOneMoveDown,
			
			PlayerTwoMoveLeft,
			PlayerTwoMoveRight,
			PlayerTwoMoveUp,
			PlayerTwoMoveDown,

			TeleAlly, 
			TeleEnemy,
			TeleToAlly,
			TeleToEnemy,
			ActionCount
		};


	public:
								Player(SceneNode* sceneGraph = nullptr);

		void					handleEvent(const sf::Event& event, CommandQueue& commands);
		void					handleRealtimeInput(CommandQueue& commands);

		void					assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key		getAssignedKey(Action action) const;


	private:
		void					initializeActions();
		static bool				isRealtimeAction(Action action);


	private:
		SceneNode*								mSceneGraph;
		std::map<sf::Keyboard::Key, Action>		mKeyBinding;
		std::map<Action, Command>				mActionBinding;
};
