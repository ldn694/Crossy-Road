#include "Land.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Rock.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <time.h>
#include <stdlib.h>



Land::Land(const TextureHolder& textures, Difficulty difficulty) : Road(Textures::Land, textures, Road::Type::Land, Zone::Safety::Safe, difficulty){
    int numberRocks = rand() % (MAX_NUMBER_ROCKS + 1);
    for (int i = 0; i < numberRocks; i++){
        int type = rand() % Rock::NumTypes;
        float x = rand() % 500 + 1;
        Rock::Type rockType;
        switch (type){
        case 0:
            rockType = Rock::Type::Rock1;
            break;
        }
        std::unique_ptr<Rock> rock(new Rock(rockType, textures));
        rock->setPosition(x, HEIGHT_SIZE / 2.0f);
        addEntity(std::move(rock));
    }
}
void Land::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
