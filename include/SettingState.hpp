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
        enum ClickableID {
			Sound,
			Music,
			Back,
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            PlayerOneMoveLeft,
            PlayerOneMoveRight,
            PlayerOneMoveUp,
            PlayerOneMoveDown,
            PlayerTwoMoveLeft,
            PlayerTwoMoveRight,
            PlayerTwoMoveUp,
            PlayerTwoMoveDown,
            SetPlayer1,
            SetPlayer2,
		};
        enum Data {
            SoundVolume,
            MusicVolume,
            P1Left,
            P1Right,
            P1Up,
            P1Down,
            P2Left,
            P2Right,
            P2Up,
            P2Down,      
        };
                                SettingState(StateStack& stack, States::ID stateID, Context context, State::Info info = State::Info());
		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);

        void                    updateFile();

		void					updateOptionText();
                                ~SettingState();
    private:
    public:
        static std::string          getData(std::vector<std::string>& data, Data type);
        static bool                 checkValidSettings(const std::string& path);
        static void                 createDefaultData();
        static const std::string    mSettingsPath;
        static bool                 pendingUpdated();
    private:
        static bool                 mPendingUpdate;
        sf::Sprite				    mBackgroundSprite;
		std::vector<sf::Text>	    mOptions;
		std::size_t				    mOptionIndex;
        ClickableList               mClickableList;
        std::size_t                 mChoiceIndex;
        ScrollBarList               mScrollBarList;
        sf::Music                   mMusic;
        std::vector <std::string>   mData;
        bool                        c[8];

        
};