#pragma once
#include"State.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Button.hpp"
#include "Choice.hpp"
#include "ClickableList.hpp"
#include "ScrollBar.hpp"
#include "ScrollBarList.hpp"
#include <SFML/Window/Keyboard.hpp>
class SettingState : public State{
    public:
                                SettingState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());
		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);

		void					updateOptionText();
        std::string             keyCodeToString(sf::Keyboard::Key keyCode);
        sf::Keyboard::Key       stringToSFMLKey(const std::string& keyString);
                                ~SettingState();
        enum ClickableID {
			Sound,
			Music,
			Back,
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            P11,
            P12,
            P13,
            P14,
            P21,
            P22,
            P23,
            P24,
            SetPlayer1,
            SetPlayer2,
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
        ScrollBarList           mScrollBarList;
        sf::Music               mMusic;
        bool                    c[8];

        
};