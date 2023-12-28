#include "GameState.hpp"
#include <iostream>
#include "Animal.hpp"
#include "GameStatus.hpp"

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

std::vector <Animal::Type> toAnimalTypes(std::vector <std::string> animalTypes) {
	std::vector <Animal::Type> result;
	for (int i = 0; i < animalTypes.size(); i++) {
		result.push_back(toAnimalType(animalTypes[i]));
	}
	return result;
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
, mWorld(*context.window, context, stateInfo.floatList[0], 
		std::vector <Animal::Type>(stateInfo.floatList[0], toAnimalType(stateInfo.stringList[2])), 
		std::vector <std::string>(stateInfo.floatList[0], stateInfo.stringList[0]), toDifficulty(stateInfo.stringList[1]))
, mContext(context)
, mPlayerNames(std::vector <std::string>(stateInfo.floatList[0], stateInfo.stringList[0]))
, mStartDifficulty(toDifficulty(stateInfo.stringList[1]))
{
	mPlayer = std::move(Player(&mWorld.getSceneGraph()));
	// std::cerr << "GameState::GameState()\n";
	//floatList[0] = 1 if 1 player, 2 if 2 players
	//stringList[0] = player1 name
	// for (int i = 0; i < stateInfo.floatList.size(); i++) {
	// 	std::cerr << stateInfo.floatList[i] << " ";
	// }
	mCurrentScoreText.setFont(context.fonts->get(Fonts::Bungee));
	setCurrentScore();
	mCurrentScoreText.setCharacterSize(20);
	mCurrentScoreText.setFillColor(sf::Color::White);
	mCurrentScoreText.setPosition(10, 10);
	update(sf::Time::Zero);
	handleEvent(sf::Event());
}

void GameState::draw()
{
	mWorld.draw();
	mContext.window->setView(mContext.window->getDefaultView());
	mContext.window->draw(mCurrentScoreText);
}

bool GameState::update(sf::Time dt) {
	try {
		mWorld.update(dt);
		CommandQueue& commands = mWorld.getCommandQueue();
		mPlayer.handleRealtimeInput(commands);
		setCurrentScore();
	}
	catch (GameStatus status) {
		int numPlayer = mPlayerNames.size();
		if (numPlayer == 1) {
			State::Info info;
			info.floatList = {float(mWorld.getCurrentScore()), float(mStartDifficulty)};
			info.stringList = mPlayerNames;
			requestStackPush(States::GameOver, info);
		}
		else {
			int lostPlayerID = mWorld.getLostPlayerID(status.mEntity);
			State::Info info;
			info.floatList = {float(lostPlayerID)};
			info.stringList = mPlayerNames;
			requestStackPush(States::GameOver, info);
		}
	}
	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	try {
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

	}
	catch (GameStatus status) {
		int numPlayer = mPlayerNames.size();
		if (numPlayer == 1) {
			State::Info info;
			info.floatList = {float(mWorld.getCurrentScore()), float(mStartDifficulty)};
			info.stringList = mPlayerNames;
			requestStackPush(States::GameOver, info);
		}
		else {
			int lostPlayerID = mWorld.getLostPlayerID(status.mEntity);
			State::Info info;
			info.floatList = {float(lostPlayerID)};
			info.stringList = {mPlayerNames};
			requestStackPush(States::GameOver, info);
		}
	}
	return false;
}

void GameState::setCurrentScore() {
	mCurrentScoreText.setString("Score: " + std::to_string(mWorld.getCurrentScore()));
}