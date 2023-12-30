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
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
		Consolas,
		T1,
		T2
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;