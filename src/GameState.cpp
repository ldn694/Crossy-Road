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
, mWorld(*context.window, context, toAnimalType(stateInfo.stringList[2]), stateInfo.stringList[0], toDifficulty(stateInfo.stringList[1]))
, mContext(context)
, mPlayerName(stateInfo.stringList[0])
, mStartDifficulty(toDifficulty(stateInfo.stringList[1]))
{
	mPlayer = std::move(Player(&mWorld.getSceneGraph()));
	std::cerr << "GameState::GameState()\n";
	//floatList[0] = 1 if 1 player, 2 if 2 players
	//stringList[0] = player1 name
	for (int i = 0; i < stateInfo.floatList.size(); i++) {
		std::cerr << stateInfo.floatList[i] << " ";
	}
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
		State::Info info;
		info.floatList = {float(mWorld.getCurrentScore()), float(mStartDifficulty)};
		info.stringList = {mPlayerName};
		requestStackPush(States::GameOver, info);
	}
	return true;
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
		State::Info info;
		info.floatList = {float(mWorld.getCurrentScore())};
		requestStackPush(States::GameOver, info);
	}
	return true;
}

void GameState::setCurrentScore() {
	mCurrentScoreText.setString("Score: " + std::to_string(mWorld.getCurrentScore()));
}