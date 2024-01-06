#include <iostream>
#include <SFML/Audio/Listener.hpp>

#include "GameState.hpp"
#include "Animal.hpp"
#include "GameStatus.hpp"

Animal::Type toAnimalType(std::string animalType) {
	if (animalType == "Cat") {
		return Animal::Cat;
	}
	else if (animalType == "Chicken") {
		return Animal::Chicken;
	}
	else if (animalType == "Lion") {
		return Animal::Lion;
	}
	else if (animalType == "Pig") {
		return Animal::Pig;
	}
	else if (animalType == "Fox") {
		return Animal::Fox;
	}
	else {
		return Animal::NumAnimalTypes;
	}
}

SoundEffect::ID toDeathSound(Animal::Type animalType) {
	if (animalType == Animal::Cat) {
		return SoundEffect::Dead_Cat;
	}
	else if (animalType == Animal::Chicken) {
		return SoundEffect::Dead_Chicken;
	}
	else if (animalType == Animal::Lion) {
		return SoundEffect::Dead_Lion;
	}
	else if (animalType == Animal::Pig) {
		return SoundEffect::Dead_Pig;
	}
	else if (animalType == Animal::Fox) {
		return SoundEffect::Dead_Fox;
	}
	else {
		return SoundEffect::Mouse_Click;
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
	}
	else if (difficulty == "Medium") {
		return Medium;
	}
	else if (difficulty == "Hard") {
		return Hard;
	}
	else {
		return NumDifficulties;
	}
}

GameState::~GameState() {
	getContext().settings->setGameSounds(nullptr);
	getContext().settings->setPlayer(nullptr);
}

GameState::GameState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context)
	, mWorld(*context.window, context, stateInfo.floatList[0],
		std::vector <Animal::Type>({ toAnimalType(stateInfo.stringList[2]),toAnimalType(stateInfo.stringList[4]) }),
		std::vector <std::string>({ stateInfo.stringList[0], stateInfo.stringList[3] }), toDifficulty(stateInfo.stringList[1]))
	, mPlayerNames(stateInfo.floatList[0] == 1 ? std::vector <std::string>({ stateInfo.stringList[0] }) : std::vector <std::string>({ stateInfo.stringList[0], stateInfo.stringList[3] }))
	, mStartDifficulty(toDifficulty(stateInfo.stringList[1]))
{
	context.settings->setGameSounds(&mWorld.getSoundPlayer());
	context.music->stopAllMusic();
	mPlayer = std::move(Player(&mWorld.getSceneGraph()));
	context.settings->setPlayer(&mPlayer);
	mCurrentScoreText.setFont(context.fonts->get(Fonts::Bungee));
	setCurrentScore();
	mCurrentScoreText.setCharacterSize(20);
	mCurrentScoreText.setFillColor(sf::Color::White);
	mCurrentScoreText.setPosition(10, 10);
	update(sf::Time::Zero);
	firstTrueUpdate = true;
	handleEvent(sf::Event());
}

void GameState::draw()
{
	mWorld.draw();
	Context context = getContext();
	if (mPlayerNames.size() == 1) {
		context.window->setView(context.window->getDefaultView());
		context.window->draw(mCurrentScoreText);
	}
}

void GameState::endGame(GameStatus status) {
	mWorld.getSoundPlayer().pauseAllSounds();
	getContext().sounds->setListenerPosition(sf::Vector2f(0.f, 0.f));
	Entity* entity = status.mEntity;
	assertThrow(dynamic_cast<Animal*>(entity) != nullptr, "GameState::endGame() entity is not an animal");
	Animal* animal = static_cast<Animal*>(entity);
	if (status.mReason == GameStatus::Drowned) {
		sf::Sound& sound = getContext().sounds->play(SoundEffect::Water_Splash, 1.f);
		sound.setPosition(0.f, 0.f, 0.f);
		sound.setRelativeToListener(true);
	}
	else if (status.mReason == GameStatus::Crashed) {
		sf::Sound& sound = getContext().sounds->play(toDeathSound(animal->getType()), 1.f);
		sound.setPosition(0.f, 0.f, 0.f);
		sound.setRelativeToListener(true);
	}
	int numPlayer = mPlayerNames.size();
	if (numPlayer == 1) {
		State::Info info;
		info.floatList = { float(mWorld.getCurrentScore()), float(mStartDifficulty) };
		info.stringList = mPlayerNames;
		requestStackPush(States::GameOver, info);
	}
	else {
		int lostPlayerID = mWorld.getLostPlayerID(status.mEntity);
		State::Info info;
		info.floatList = { float(lostPlayerID) };
		info.stringList = mPlayerNames;
		requestStackPush(States::GameOver, info);
	}
	draw();
}

bool GameState::update(sf::Time dt) {
	try {
		if (firstTrueUpdate) {
			if (getContext().music->getStatus(Music::IngameTheme) != sf::Music::Playing) {
				getContext().music->stopAllMusic();
				getContext().music->play(Music::IngameTheme);
			}
			firstTrueUpdate = false;
		}
		mWorld.getSoundPlayer().playAllSounds();
		mWorld.update(dt);
		CommandQueue& commands = mWorld.getCommandQueue();
		mPlayer.handleRealtimeInput(commands);
		setCurrentScore();
	}
	catch (GameStatus status) {
		endGame(status);
	}
	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	try {
		// Game input handling
		CommandQueue& commands = mWorld.getCommandQueue();
		mPlayer.handleEvent(event, commands);

		while (pendingNotification()) {

		}

		// Escape pressed, trigger the pause screen
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			mWorld.getSoundPlayer().pauseAllSounds();
			firstTrueUpdate = true;
			requestStackPush(States::Pause);
		}

	}
	catch (GameStatus status) {
		endGame(status);
	}
	return false;
}

void GameState::setCurrentScore() {
	mCurrentScoreText.setString("Score: " + std::to_string(mWorld.getCurrentScore()));
}