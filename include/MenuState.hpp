#pragma once
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.hpp"
#include "ClickableList.hpp"


class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);

		void					updateOptionText();
		enum ClickableID {
			Button1,
			Button2,
			Play,
			Load,
			Set,
			Score,
			Exit,
		};


	private:
		enum OptionNames
		{
			
		};


	private:
		sf::Sprite				mBackgroundSprite;
		ClickableList			mClickableList;
		std::vector<sf::Text>	mOptions;
		std::size_t				mOptionIndex;

		int						page;

};
