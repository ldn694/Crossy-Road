#include "Application.hpp"
#include "Utility.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "SettingState.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"
#include "GameStartState.hpp"
#include "GameOverState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "LoadingState.hpp"
#include "ScoreboardState.hpp"

#include <SFML/Audio/Listener.hpp>
#include <iostream>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application(sf::ContextSettings contextSettings)
	: mWindow(sf::VideoMode(1050, 600), "States", sf::Style::Close, contextSettings), mTextures(), mFonts(), mSounds(), mScoreboard(), mMusic(), mStateStack(Context(mWindow, mTextures, mFonts, mSounds, mMusic, mScoreboard, mSettings)), mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0)
{
	mSettings.setSoundPlayer(&mSounds);
	mWindow.setKeyRepeatEnabled(false);
	srand(time(NULL));
	mFonts.load(Fonts::Main, "Assets/Fonts/Sansation.ttf");
	mFonts.load(Fonts::T1, "Assets/Fonts/Colo-Pro.otf");
	mFonts.load(Fonts::T2,"Assets/Fonts/MOTTCI.ttf");
	mFonts.load(Fonts::Bungee,"Assets/Fonts/Bungee-Regular.otf");

	mTextures.load(Textures::TitleScreen, "Assets/Images/TitleScreen.png");
    mTextures.load(Textures::SettingBackground, "Assets/Images/SettingBackground.png");
	mFonts.load(Fonts::T1, "Assets/Fonts/Colo-Pro.otf");
	mFonts.load(Fonts::T2,"Assets/Fonts/MOTTCI.ttf");
	mFonts.load(Fonts::Bungee, "Assets/Fonts/Bungee-Regular.otf");
	mTextures.load(Textures::M1, "Assets/Images/M1.PNG");
	mTextures.load(Textures::M2, "Assets/Images/ForMenu/M2.PNG");
	mTextures.load(Textures::ScoreBoard_Background, "Assets/Images/ForScore/scoreboard.png");
	
	mSounds.load(SoundEffect::Water_Splash, "Assets/Sounds/Water_Splash.wav");
	mSounds.setListenerPosition(sf::Vector2f(0.f, 0.f));

	mMusic.play(Music::MenuTheme);

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	//top right
	mStatisticsText.setPosition(1045, 5);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));
		mStatisticsText.setOrigin(mStatisticsText.getLocalBounds().width + mStatisticsText.getLocalBounds().left, 0);

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<GameStartState>(States::GameStart);
	mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingState>(States::Setting);
	mStateStack.registerState<GameOverState>(States::GameOver);
	mStateStack.registerState<ScoreboardState>(States::Scoreboard);
	mStateStack.registerState<LoadingState>(States::Loading);
}
