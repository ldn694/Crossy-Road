#pragma once

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "GameStatus.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
public:
	GameState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());

	virtual          	~GameState();

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);
private:
	void				setCurrentScore();
	void 				endGame(GameStatus status);


private:
	bool 							firstTrueUpdate = false;
	Player							mPlayer;
	World							mWorld;
	std::vector <std::string> 		mPlayerNames;
	sf::Text 						mCurrentScoreText;
	Difficulty 						mStartDifficulty;
};