#pragma once

#include <string>

// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		Player				= 1 << 1,
		PlayerOne			= 1 << 2,
		PlayerTwo			= 1 << 3,
		FakeEntity			= 1 << 4,
		Obstacle			= 1 << 5,
		Hostile				= 1 << 6,
		SafeZone			= 1 << 7,
		DeadZone			= 1 << 8,
		AlliedAircraft		= 1 << 9,
		EnemyAircraft		= 1 << 10,
		NumCategory			= 11,
	};
}

std::string toString(Category::Type type);
std::string fromCategoryToString(int category);
