#pragma once

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Player.hpp"
#include "StateStack.hpp"
#include "Scoreboard.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>


class Application
{
	public:
								Application(sf::ContextSettings settings);
		void					run();
		

	private:
		void					processInput();
		void					update(sf::Time dt);
		void					render();

		void					updateStatistics(sf::Time dt);
		void					registerStates();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		TextureHolder			mTextures;
	  	FontHolder				mFonts;
		Scoreboard				mScoreboard;
		// Player					mPlayer;
		sf::Music               backgroundmusic;
		StateStack				mStateStack;

		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};
