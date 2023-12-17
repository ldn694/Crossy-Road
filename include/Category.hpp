#pragma once


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		Player				= 1 << 1,
		Safespot			= 1 << 2,
		Obstacle			= 1 << 3,
		Hostile				= 1 << 4,
		FakeEntity			= 1 << 5,
		AlliedAircraft		= 1 << 6,
		EnemyAircraft		= 1 << 7,
	};
}
