#include "Land.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Rock.hpp"
#include "Tree.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <time.h>
#include <stdlib.h>


int Land::getNumberObstacles(Variant variant){
    switch (variant){
    case Land::Variant::Empty:
        return 0;
    case Land::Variant::Normal:
        return rand() % MAX_NUMBER_OBSTACLE + 1;
    case Land::Variant::Start:
        return rand() % (MAX_NUMBER_OBSTACLE / 2) + 1;
    }
    return 0;
}

Textures::ID toTextureID(Land::Variant variant){
    switch (variant){
    case Land::Variant::Empty:
        return Textures::NormalLand;
    case Land::Variant::Start:
        return Textures::StartLand;
    case Land::Variant::Normal:
        return Textures::NormalLand;
    }
    return Textures::NormalLand;
}

Land::Land(const TextureHolder& textures, Difficulty difficulty, int variant) : Road(toTextureID(static_cast<Land::Variant>(variant)), textures, Road::Type::Land, Zone::Safety::Safe, difficulty){
    int numberRocks = getNumberObstacles(static_cast<Variant>(variant));
    std::vector <int> index = randomIntSampling(NUM_ZONE, numberRocks);
    for (int i = 0; i < numberRocks; i++){
        int obstacleType = rand() % 2;
        if (obstacleType == 0){
            int type = rand() % Tree::NumTypes;
            Tree::Type treeType = static_cast<Tree::Type>(type);
            std::unique_ptr<Tree> tree(new Tree(treeType, textures));
            tree->setPosition(mZones[index[i]]->getPosition());
            addEntity(std::move(tree));
        }
        else {
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
}
void Land::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
