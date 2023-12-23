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
		Choice,
		PressedChoice,
		HoveredChoice,
		GameStartBackground,
		LeftArrowButton,
		LeftHoveredArrowButton,
		RightArrowButton,
		RightHoveredArrowButton,
		Railways,
		SRoad,
		River,
		Land,
		SettingBackground,
		Rock1,
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
		ZebraUp,
		ZebraDown,
		ZebraLeft,
		ZebraRight,
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
		Bungee
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;