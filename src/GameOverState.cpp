#include "GameOverState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>


GameOverState::GameOverState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context),
	mClickableList(context)
{
	loadTextures(context);
	sf::Font& font = context.fonts->get(Fonts::Bungee);
	sf::Vector2f viewSize = context.window->getView().getSize();
	
	mBackgroundSprite.setTexture(context.textures->get(Textures::GameOverBackground));
	setSize(mBackgroundSprite, viewSize);
	mBackgroundSprite.setColor(sf::Color(255, 255, 255, 220));
	/*mGameOverdText.setFont(font);
	mGameOverdText.setString("Game GameOverd");
	mGameOverdText.setCharacterSize(70);
	centerOrigin(mGameOverdText);
	mGameOverdText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("(Press Backspace to return to the main menu)");
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);*/

	mClickableList.registerClickable<Button>(Clickable::Type::Button);
	Clickable::Info info;

	info.floatList = { 525 - 65 - 250, 250, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::GameOverToHome, Textures::GameOverToHomeHovered };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Home, info);

	info.floatList = { 525 - 65, 250, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::GameOverRetry, Textures::GameOverRetryHovered };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Retry, info);

	info.floatList = { 525 - 65 + 250, 250, 130, 130, 10 };
	info.stringList = { "" };
	info.status = Clickable::Status(true, true, true);
	info.fontIDList = { Fonts::Main };
	info.textureIDList = { Textures::GameOverToLeaderboard, Textures::GameOverToLeaderboardHovered };
	info.colorList = { sf::Color::White };
	mClickableList.addClickable(Clickable::Type::Button, ButtonNames::Leaderboard, info);

	assertThrow(stateInfo.stringList.size() == 1 || stateInfo.stringList.size() == 2, "GameOverState: stateInfo.stringList.size() != 1 or 2");
	int numPlayer = stateInfo.stringList.size();
	if (numPlayer == 1) {
		assertThrow(stateInfo.floatList.size() == 2, "GameOverState: stateInfo.floatList.size() != 2");
		assertThrow(stateInfo.stringList.size() == 1, "GameOverState: stateInfo.stringList.size() != 1");
		int score = int(stateInfo.floatList[0]);
		std::string name = stateInfo.stringList[0];
		int difficulty = int(stateInfo.floatList[1]);

		mResult.setFont(font);
		mResult.setStyle(sf::Text::Bold);
		mResult.setString("Your score: " + std::to_string(score));
		mResult.setCharacterSize(90);
		centerOrigin(mResult);
		mResult.setPosition(0.5f * viewSize.x, 0.2f * viewSize.y);

		context.scoreboard->addNewScore(Difficulty(difficulty), name, score);
	}
	else {
		assertThrow(stateInfo.floatList.size() == 1, "GameOverState: stateInfo.floatList.size() != 1");
		assertThrow(stateInfo.stringList.size() == 2, "GameOverState: stateInfo.stringList.size() != 2");
		int lostPlayerID = int(stateInfo.floatList[0]);
		int wonPlayerID = 1 - lostPlayerID;
		std::string loserName = stateInfo.stringList[lostPlayerID];
		std::string winnerName = stateInfo.stringList[wonPlayerID];
		if (loserName == winnerName) {
			loserName += " " + std::to_string(lostPlayerID + 1);
			winnerName += " " + std::to_string(wonPlayerID + 1);
		}

		mResult.setFont(font);
		mResult.setStyle(sf::Text::Bold);
		mResult.setString(winnerName + " won!");
		mResult.setCharacterSize(90);
		centerOrigin(mResult);
		mResult.setPosition(0.5f * viewSize.x, 0.2f * viewSize.y);
	
	}
}
void GameOverState::loadTextures(Context  context)
{
	context.textures->load(Textures::GameOverToHome, "Assets/Images/ForGameOver/home_button.png");
	context.textures->load(Textures::GameOverToHomeHovered, "Assets/Images/ForGameOver/home_button_hover.png");
	context.textures->load(Textures::GameOverRetry, "Assets/Images/ForGameOver/retry_button.png");
	context.textures->load(Textures::GameOverRetryHovered, "Assets/Images/ForGameOver/retry_button_hover.png");
	context.textures->load(Textures::GameOverToLeaderboard, "Assets/Images/ForGameOver/leaderboard_button.png");
	context.textures->load(Textures::GameOverToLeaderboardHovered, "Assets/Images/ForGameOver/leaderboard_button_hover.png");
	context.textures->load(Textures::GameOverBackground, "Assets/Images/ForGameOver/background.png");
}
void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	mClickableList.draw();
    window.draw(mResult);
}

bool GameOverState::update(sf::Time)
{
	return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
	mClickableList.handleEvent(event);
	while (mClickableList.pendingAnnouncement()) {
		Clickable::Announcement announcement = mClickableList.popAnnouncement();
		if (announcement.action == Clickable::LeftPressed) {
			// std::cout << "Left Clicked " << announcement.id << "\n";
            if (announcement.id == ButtonNames::Home) {
				requestStateClear();
				requestStackPush(States::Menu);
				//State::Info info;
				//info.stringList = { "Hello from GameOverState to MenuState" };
				//requestNotifyState(States::Menu, info);
			}
			else if (announcement.id == ButtonNames::Retry) {
				// requestStateClear();
                // requestStackPush(States::Menu);
                // requestStackPush(States::GameStart);
				requestStackPop();
				requestStackPop();
				//State::Info info;
				//requestNotifyState(States::Game, info);
			}
			else if (announcement.id == ButtonNames::Leaderboard) {
				requestStackPush(States::Scoreboard);
				//State::Info info;
				//info.stringList = { "Hello from GameOverState to SettingState" };
				//requestNotifyState(States::Setting, info);
			}
		}
		else if (announcement.action == Clickable::RightPressed) {
			// std::cout << "Right Clicked " << announcement.id << "\n";
		}
	}
	while (pendingNotification()) {
		State::Info info = popNotification();
		// std::cout << info.stringList[0] << "\n";
	}
	return false;
}