#include "LoadingState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


LoadingState::LoadingState(StateStack& stack, States::ID stateID, Context context, State::Info info)
: State(stack, stateID, context)
{
	sf::RenderWindow& window = *getContext().window;
	sf::Font& font = context.fonts->get(Fonts::Bungee);
	sf::Vector2f viewSize = window.getView().getSize();
	
	mClock.restart();
	mCount = 0;

	mString = "3";
	mLoadingText.setFont(font);
	mLoadingText.setCharacterSize(100);
	mLoadingText.setString(mString);
	centerOrigin(mLoadingText);
	mLoadingText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);

	context.textures->load(Textures::PauseBackground, "Assets/Images/ForPause/background.png");
	mBackgroundSprite.setTexture(context.textures->get(Textures::PauseBackground));
	setSize(mBackgroundSprite, viewSize);
	mBackgroundSprite.setColor(sf::Color(255, 255, 255, 200));

}

void LoadingState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mLoadingText);
}

bool LoadingState::update(sf::Time)
{
	if (mClock.getElapsedTime().asSeconds() >= 1.f) {
		mCount++;
		if (mCount == 3){
			requestStackPop();
		}
		mString = std::to_string(3 - mCount);
		mLoadingText.setString(mString);
		mClock.restart();
	}
	return false;
}

bool LoadingState::handleEvent(const sf::Event& event)
{
	return false;
}

