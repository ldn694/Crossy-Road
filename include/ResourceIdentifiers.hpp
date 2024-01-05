#pragma once


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
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
		KeyBinding,
		KeyBinding_,
		SetPlayer1,
		SetPlayer2,
		//SRoad
		RedCarRight, RedCarLeft,
		BlueCarRight, BlueCarLeft,
		TruckRight, TruckLeft,
		VanRight, VanLeft,
		SRoad_Default, SRoad_Line, SRoad_Stripe,		
		StopLightRed, StopLightGreen, StopLightYellow,
		//LandWithAnimal
		Pig1, Pig2, Pig3, Pig4,
		Lion1, Lion2, Lion3, Lion4,
		Fox1, Fox2, Fox3, Fox4,
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

namespace SoundEffect
{
	enum ID
	{
		Animal_Jump,
		Water_Splash,
		Train_Incoming,
		Train_Passing,
		Car_Honk,
		Mouse_Click,
		Mouse_Hover,
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		IngameTheme,
		GameOverTheme,
		NumMusic,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;