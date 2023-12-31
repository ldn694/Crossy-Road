#pragma once


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert,
		TitleScreen,
		M1,
		M2,
		Button,
		PressedButton,
		Play,
		Play_,
		Load,
		Load_,
		Set,
		Set_,
		Score,
		Score_,
		Exit,
		Exit_,
		Dog,
		//GameStartState
		EasyChoice,
		EasyPressedChoice,
		EasyHoveredChoice,
		MediumChoice,
		MediumPressedChoice,
		MediumHoveredChoice,
		HardChoice,
		HardPressedChoice,
		HardHoveredChoice,
		OnePlayerChoice,
		OnePlayerPressedChoice,
		OnePlayerHoveredChoice,
		TwoPlayer,
		TwoPlayerPressedChoice,
		TwoPlayerHoveredChoice,
		GameStartBackground,
		Quit,
		QuitHovered,
		Next,
		NextHovered,
		SelectLeft,
		SelectLeftHovered,
		SelectRight,
		SelectRightHovered,
		TypeBox,
		TypeBoxHovered,
		TypeBoxInput,
		//Character
		Cat,
		Chicken,
		Fox,
		Pig,
		Lion,
		//Railways
		Railways, Train,
		TrafficLight,
		TrafficLight1,
		TrafficLight2,
		//River
		RiverLeftToRight, RiverRightToLeft,
		Lily, SmallLog, BigLog,
		//Land
		NormalLand, StartLand,
		Rock1,
		SmallTree, MediumTree, BigTree,
		SettingBackground,
		Sound,
		Sound_,
		Music,
		Music_,
		Back,
        Back_,
		MoveLeft,
		MoveLeft_,
		MoveRight,
		MoveRight_,
		MoveUp,
		MoveUp_,
		MoveDown,
		MoveDown_,
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
		P11_,
		P12_,
		P13_,
		P14_,
		P21_,
		P22_,
		P23_,
		P24_,		//SRoad
		RedCarRight, RedCarLeft,
		BlueCarRight, BlueCarLeft,
		TruckRight, TruckLeft,
		VanRight, VanLeft,
		SRoad_Default, SRoad_Line, SRoad_Stripe,		
		StopLightRed, StopLightGreen, StopLightYellow,
		//Cat
		CatUp,
		CatDown,
		CatLeft,
		CatRight,
		//Chicken
		ChickenUp,
		ChickenDown,
		ChickenLeft,
		ChickenRight,
		//Fox
		FoxUp,
		FoxDown,
		FoxLeft,
		FoxRight,
		//Pig
		PigUp,
		PigDown,
		PigLeft,
		PigRight,
		//Zebra
		LionUp,
		LionDown,
		LionLeft,
		LionRight,
		//GameOver state
		GameOverBackground,
		GameOverToLeaderboard,
		GameOverToLeaderboardHovered,
		GameOverRetry,
		GameOverRetryHovered,
		GameOverToHome,
		GameOverToHomeHovered,
		//Pause State
		Home,
		Home_Hover,
		Resume,
		Resume_Hover,
		Setting,
		Setting_Hover,
		PauseBackground,
		
		//ScoreBoard
		ScoreBoard_Background,
		ID1,
		ID2,
		ID3,
		ID4,
		ID5,
		scoreboard_quit,
		scoreboard_quit_hover,
		mode,
		scoreboard_left,
		scoreboard_left_hover,
		scoreboard_right,
		scoreboard_right_hover,
		scoreboard_score,
		scoreboard_score_hover,
		scoreboard_name,
		scoreboard_name_hover,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
		Consolas,
		T1,
		T2,
		Bungee,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;