#include "Land.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Rock.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <time.h>
#include <stdlib.h>


int Land::getNumberRocks(Variant variant){
    switch (variant){
    case Land::Variant::Empty:
        return 0;
    case Land::Variant::Normal:
        return rand() % (MAX_NUMBER_ROCKS + 1);
    }
    return 0;
}

Land::Land(const TextureHolder& textures, Difficulty difficulty, int variant) : Road(Textures::Land, textures, Road::Type::Land, Zone::Safety::Safe, difficulty){
    int numberRocks = getNumberRocks(static_cast<Variant>(variant));
    std::vector <int> index = randomIntSampling(NUM_ZONE, numberRocks);
    for (int i = 0; i < numberRocks; i++){
        int type = rand() % Rock::NumTypes;
        Rock::Type rockType;
        switch (type){
        case 0:
            rockType = Rock::Type::Rock1;
            break;
        }
        std::unique_ptr<Rock> rock(new Rock(rockType, textures));
        rock->setPosition(mZones[index[i]]->getPosition());
        addEntity(std::move(rock));
    }
}
void Land::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
