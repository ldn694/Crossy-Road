#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"
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

struct AircraftMover
{
	AircraftMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

struct TeleportToAircraft
{
	TeleportToAircraft(sf::Time duration, sf::Vector2f offset = sf::Vector2f(0.f, 0.f))
		: duration(duration)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		auto playerAircrafts = aircraft.getRoot()->findChildrenByCategory<Aircraft>(Category::Player);
		assertThrow(playerAircrafts.size() == 1, "playerAircrafts.size() != 1");
		auto player = playerAircrafts[0];
		aircraft.addDynamicAnimation(player, duration, offset);
	}
	sf::Time duration;
	sf::Vector2f offset;
};

struct AirCraftTeleport {
	AirCraftTeleport(sf::Time duration, sf::Vector2f offset = sf::Vector2f(0.f, 0.f), bool toAlly = false)
		: duration(duration), offset(offset), toAlly(toAlly)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		if (toAlly) {
			auto allyAircrafts = aircraft.getRoot()->findChildrenByCategory<Aircraft>(Category::AlliedAircraft);
			assertThrow(allyAircrafts.size() == 1, "allyAircrafts.size() != 1");
			auto ally = allyAircrafts[0];
			aircraft.addDynamicAnimation(ally, duration, offset);
		} else {
			auto enemyAircrafts = aircraft.getRoot()->findChildrenByCategory<Aircraft>(Category::EnemyAircraft);
			assertThrow(enemyAircrafts.size() == 1, "enemyAircrafts.size() != 1");
			auto enemy = enemyAircrafts[0];
			aircraft.addDynamicAnimation(enemy, duration, offset);
		}
	}
	bool toAlly;
	sf::Time duration;
	sf::Vector2f offset;
};

Player::Player(SceneNode* sceneGraph): mSceneGraph(sceneGraph)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::U] = TeleAlly;
	mKeyBinding[sf::Keyboard::I] = TeleEnemy;
	mKeyBinding[sf::Keyboard::O] = TeleToAlly;
	mKeyBinding[sf::Keyboard::P] = TeleToEnemy;

	mActionBinding[MoveLeft].category = Category::Player;
	mActionBinding[MoveRight].category = Category::Player;
	mActionBinding[MoveUp].category = Category::Player;
	mActionBinding[MoveDown].category = Category::Player;
	mActionBinding[TeleAlly].category = Category::AlliedAircraft;
	mActionBinding[TeleEnemy].category = Category::EnemyAircraft;
	mActionBinding[TeleToAlly].category = Category::Player;
	mActionBinding[TeleToEnemy].category = Category::Player;



	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's aircraft
	// FOREACH(auto& pair, mActionBinding)
	// 	pair.second.category = Category::PlayerAircraft;
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

	// mActionBinding[MoveLeft].action	 = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	// mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	// mActionBinding[MoveUp].action    = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	// mActionBinding[MoveDown].action  = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
	mActionBinding[MoveLeft].action	 = derivedAction<Animal>(AnimalMove(Animal::Direction::Left));
	mActionBinding[MoveRight].action = derivedAction<Animal>(AnimalMove(Animal::Direction::Right));
	mActionBinding[MoveUp].action    = derivedAction<Animal>(AnimalMove(Animal::Direction::Up));
	mActionBinding[MoveDown].action  = derivedAction<Animal>(AnimalMove(Animal::Direction::Down));
	mActionBinding[TeleAlly].action  = derivedAction<Aircraft>(TeleportToAircraft(sf::seconds(1.f)));
	mActionBinding[TeleEnemy].action = derivedAction<Aircraft>(TeleportToAircraft(sf::seconds(1.f)));
	mActionBinding[TeleToAlly].action  = derivedAction<Aircraft>(AirCraftTeleport(sf::seconds(1.f), sf::Vector2f(0.f, 0.f), true));
	mActionBinding[TeleToEnemy].action = derivedAction<Aircraft>(AirCraftTeleport(sf::seconds(1.f), sf::Vector2f(0.f, 0.f), false));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		default:
			return false;
	}
}
