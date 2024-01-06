#include "TitleState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

TitleState::TitleState(StateStack& stack, States::ID stateID, Context context, State::Info info)
: State(stack, stateID, context)
, mText()
, mShowText(true)
, mTextEffectTime(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::M1));
	mBackgroundSprite.setScale(0.65,0.65);

	getContext().music->stopAllMusic();
	getContext().music->play(Music::TitleTheme);

	mText.setFont(context.fonts->get(Fonts::T1));
	mText.setString("Press any key to start");
	mText.setFillColor(sf::Color(251,224,91));
	centerOrigin(mText);
	mText.setScale(1.0,1.0);
	mText.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(10.f, 150.f));
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{	
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}