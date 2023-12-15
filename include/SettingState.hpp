#pragma once
#include"State.hpp"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class SettingState : public State{
    public:
                                SettingState(StateStack &stack,Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);

		void					updateOptionText();
    private:
    enum OptionNames
    {
        Sound,
        Music,
        Back,
    };
    private:
        sf::Sprite				mBackgroundSprite;
		std::vector<sf::Text>	mOptions;
		std::size_t				mOptionIndex;

};