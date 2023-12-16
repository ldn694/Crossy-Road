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