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
		//
		Railways,
		SRoad,
		//River
		RiverLeftToRight, RiverRightToLeft,
		Lily, SmallLog, BigLog,
		//Land
		NormalLand, StartLand,
		Rock1,
		SmallTree, MediumTree, BigTree,
		SettingBackground,
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
		//Pause State
		BackToMenu,
		BackToMenu_Hover,
		Continue,
		Continue_Hover,
		Setting,
		Setting_Hover,
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