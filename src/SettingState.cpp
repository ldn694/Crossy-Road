#include"State.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include "StateIdentifiers.hpp"
#include "SettingState.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <StateIdentifiers.hpp>

#include<iostream>
#include<string>

SettingState::SettingState(StateStack& stack, States::ID stateID, Context context, State::Info stateInfo)
	: State(stack, stateID, context), mOptions(), mOptionIndex(0), mClickableList(context)
{

	sf::Texture &texture = context.textures->get(Textures::SettingBackground);
	sf::Font &font = context.fonts->get(Fonts::Main);

	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale(1050.0f / mBackgroundSprite.getGlobalBounds().width, 600.0f / mBackgroundSprite.getGlobalBounds().height);

	// A simple setting demonstration
	sf::Text SoundOption;
	SoundOption.setFont(font);
	SoundOption.setString("Sound");
	centerOrigin(SoundOption);
	SoundOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(SoundOption);

	sf::Text MusicOption;
	MusicOption.setFont(font);
	MusicOption.setString("Music");
	centerOrigin(MusicOption);
	MusicOption.setPosition(SoundOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(MusicOption);
    

	sf::Text BackOption;
	BackOption.setFont(font);
	BackOption.setString("Back");
	centerOrigin(BackOption);
	BackOption.setPosition(MusicOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(BackOption);

	updateOptionText();
}

void SettingState::draw()
{
	sf::RenderWindow &window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text &text, mOptions)
	window.draw(text);
}

bool SettingState::update(sf::Time dt) 
{
	return true;
}

bool SettingState::handleEvent(const sf::Event &event)
{
	// The demonstration setting logic
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Sound)
		{
			
		}
		else if(mOptionIndex == Music)
		{

		}
	    else if (mOptionIndex == Back)
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}

	else if (event.key.code == sf::Keyboard::Up)
	{
		// Decrement and wrap-around
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}

	else if (event.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}

	return false;
}

void SettingState::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	FOREACH(sf::Text & text, mOptions)
	text.setColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}
