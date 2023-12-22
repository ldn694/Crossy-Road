#pragma once
#include"State.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.hpp"
#include "Choice.hpp"
#include "ClickableList.hpp"
#include "ScrollBar.hpp"
class SettingState : public State{
    public:
                                SettingState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());
		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);

		void					updateOptionText();
        enum ClickableID {
			Sound,
			Music,
			Back
		};
    private:
    enum OptionNames
    {

    };
    private:
        sf::Sprite				mBackgroundSprite;
		std::vector<sf::Text>	mOptions;
		std::size_t				mOptionIndex;
        ClickableList           mClickableList;
        std::size_t             mChoiceIndex;
        ScrollBar               mSB_Sound,mSB_Music;
        sf::Music               mMusic;
};