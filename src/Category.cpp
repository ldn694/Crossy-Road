#include "Category.hpp"

std::string toString(Category::Type type)
{
    switch (type)
    {
        case Category::None:
            return "None";
        case Category::Scene:
            return "Scene";
        case Category::Player:
            return "Player";
        case Category::FakeEntity:
            return "FakeEntity";
        case Category::Obstacle:
            return "Obstacle";
        case Category::Hostile:
            return "Hostile";
        case Category::SafeZone:
            return "SafeZone";
        case Category::DeadZone:
            return "DeadZone";
        case Category::AlliedAircraft:
            return "AlliedAircraft";
        case Category::EnemyAircraft:
            return "EnemyAircraft";
        default:
            return "Unknown";
    }
}

std::string fromCategoryToString(int category)
{
    std::string result = "";
    for (int i = 0; i < Category::NumCategory; i++)
    {
        if (category & (1 << i))
        {
            result += toString(static_cast<Category::Type>(1 << i)) + " ";
        }
    }
    return result;
}