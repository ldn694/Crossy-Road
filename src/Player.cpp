#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Animal.hpp"
#include "Foreach.hpp"
#include "Utility.hpp"

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

struct AnimalMove {
	AnimalMove(Animal::Direction direction)
		: direction(direction)
	{
	}

	void operator() (Animal& animal, sf::Time) const
	{
		animal.move(direction);
	}

	Animal::Direction direction;
};

Player::Player(SceneNode* sceneGraph): mSceneGraph(sceneGraph)
{
	// Set initial key bindings
	// mKeyBinding[sf::Keyboard::A] = PlayerOneMoveLeft;
	// mKeyBinding[sf::Keyboard::D] = PlayerOneMoveRight;
	// mKeyBinding[sf::Keyboard::W] = PlayerOneMoveUp;
	// mKeyBinding[sf::Keyboard::S] = PlayerOneMoveDown;

	// mKeyBinding[sf::Keyboard::Left] = PlayerTwoMoveLeft;
	// mKeyBinding[sf::Keyboard::Right] = PlayerTwoMoveRight;
	// mKeyBinding[sf::Keyboard::Up] = PlayerTwoMoveUp;
	// mKeyBinding[sf::Keyboard::Down] = PlayerTwoMoveDown;
	// mKeyBinding[sf::Keyboard::U] = TeleAlly;
	// mKeyBinding[sf::Keyboard::I] = TeleEnemy;
	// mKeyBinding[sf::Keyboard::O] = TeleToAlly;
	// mKeyBinding[sf::Keyboard::P] = TeleToEnemy;

	// Set initial action bindings
	mActionBinding[PlayerOneMoveLeft].category = Category::PlayerOne;
	mActionBinding[PlayerOneMoveRight].category = Category::PlayerOne;
	mActionBinding[PlayerOneMoveUp].category = Category::PlayerOne;
	mActionBinding[PlayerOneMoveDown].category = Category::PlayerOne;
	mActionBinding[PlayerTwoMoveLeft].category = Category::PlayerTwo;
	mActionBinding[PlayerTwoMoveRight].category = Category::PlayerTwo;
	mActionBinding[PlayerTwoMoveUp].category = Category::PlayerTwo;
	mActionBinding[PlayerTwoMoveDown].category = Category::PlayerTwo;


	// Set initial action bindings
	initializeActions();	
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	const float playerSpeed = 200.f;
	mActionBinding[PlayerOneMoveLeft].action	= derivedAction<Animal>(AnimalMove(Animal::Direction::Left));
	mActionBinding[PlayerOneMoveRight].action 	= derivedAction<Animal>(AnimalMove(Animal::Direction::Right));
	mActionBinding[PlayerOneMoveUp].action    	= derivedAction<Animal>(AnimalMove(Animal::Direction::Up));
	mActionBinding[PlayerOneMoveDown].action  	= derivedAction<Animal>(AnimalMove(Animal::Direction::Down));
	mActionBinding[PlayerTwoMoveLeft].action	= derivedAction<Animal>(AnimalMove(Animal::Direction::Left));
	mActionBinding[PlayerTwoMoveRight].action 	= derivedAction<Animal>(AnimalMove(Animal::Direction::Right));
	mActionBinding[PlayerTwoMoveUp].action    	= derivedAction<Animal>(AnimalMove(Animal::Direction::Up));
	mActionBinding[PlayerTwoMoveDown].action  	= derivedAction<Animal>(AnimalMove(Animal::Direction::Down));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		default:
			return false;
	}
}
