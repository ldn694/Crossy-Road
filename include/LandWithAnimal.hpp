#pragma once
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"
#include "WalkingAnimal.hpp"
//include clock of sfml
#include "SFML/System/Clock.hpp"

class LandWithAnimal : public Road {
public:
    enum Variant {
        Pig,
        Lion,
        Fox,
        NumLandWithAnimalVariants
    };
public:
    LandWithAnimal(const TextureHolder& textures, Difficulty difficulty, int variant);
    virtual void updateCurrent(sf::Time dt);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    WalkingAnimal* animal;
    SceneNode* mediateNode;
    sf::Time mTime[2] = {sf::seconds(2.0f), sf::seconds(4.0f)};
    sf::Clock mClock, mChangeStateClock;
    int curStatus, curDirection;
};


