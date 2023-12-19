#pragma once


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		Player				= 1 << 1,
		FakeEntity			= 1 << 2,
		Obstacle			= 1 << 3,
		Hostile				= 1 << 4,
		SafeZone			= 1 << 5,
		DeadZone			= 1 << 6,
		AlliedAircraft		= 1 << 7,
		EnemyAircraft		= 1 << 8,
	};
}
