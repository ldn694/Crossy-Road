#include "GameState.hpp"
#include <iostream>
#include "Animal.hpp"

Animal::Type toAnimalType(std::string animalType) {
	if (animalType == "Cat") {
		return Animal::Cat;
	} else if (animalType == "Chicken") {
		return Animal::Chicken;
	} else if (animalType == "Lion") {
		return Animal::Lion;
	} else if (animalType == "Pig") {
		return Animal::Pig;
	} else if (animalType == "Fox") {
		return Animal::Fox;
	} else {
		return Animal::NumAnimalTypes;
	}
}

Difficulty toDifficulty(std::string difficulty) {
	if (difficulty == "Easy") {
		return Easy;
	} else if (difficulty == "Medium") {
		return Medium;
	} else if (difficulty == "Hard") {
		return Hard;
	} else {
		return NumDifficulties;
	}
}

GameState::GameState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
: State(stack, stateID, context)
, mWorld(*context.window, toAnimalType(stateInfo.stringList[2]), stateInfo.stringList[0], toDifficulty(stateInfo.stringList[1]))
{
	mPlayer = std::move(Player(&mWorld.getSceneGraph()));
	std::cerr << "GameState::GameState()\n";
	//floatList[0] = 1 if 1 player, 2 if 2 players
	//stringList[0] = player1 name
	for (int i = 0; i < stateInfo.floatList.size(); i++) {
		std::cerr << stateInfo.floatList[i] << " ";
	}
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt) {
	mWorld.update(dt);
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// while (pendingNotification()) {
	// 	State::Info info = popNotification();
	// 	for (int i = 0; i < info.floatList.size(); i++) {
	// 		std::cerr << info.floatList[i] << " ";
	// 	}
	// 	std::cerr << "\n";
	// }

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}