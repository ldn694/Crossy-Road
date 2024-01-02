#include "WalkingAnimal.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


WalkingAnimal::WalkingAnimal(Type type, sf::Vector2f position, const TextureHolder& textures, Road* road):
    textures(textures)
{
    std::cout << "Hello\n";
    std::cout << type << "\n";
    switch (type)
    {
    case WalkingAnimal::Pig:
        std::cout << "Pig\n";
        mSprite[0].setTexture(textures.get(Textures::Pig1));
        mSprite[1].setTexture(textures.get(Textures::Pig2));
        mSprite[2].setTexture(textures.get(Textures::Pig3));
        mSprite[3].setTexture(textures.get(Textures::Pig4));
        break;
    case WalkingAnimal::Lion:
        std::cout << "Lion\n";
        mSprite[0].setTexture(textures.get(Textures::Lion1));
        mSprite[1].setTexture(textures.get(Textures::Lion2));
        mSprite[2].setTexture(textures.get(Textures::Lion3));
        mSprite[3].setTexture(textures.get(Textures::Lion4));
        break;
    case WalkingAnimal::Fox:   
        std::cout << "Fox\n";
        mSprite[0].setTexture(textures.get(Textures::Fox1));
        mSprite[1].setTexture(textures.get(Textures::Fox2));
        mSprite[2].setTexture(textures.get(Textures::Fox3));
        mSprite[3].setTexture(textures.get(Textures::Fox4));
        break;
    default:
        break;
    }
    float width, height;
    width = WIDTH_SIZE;
    height = HEIGHT_SIZE;
    for (int i=0; i<4; i++){
        setSize(mSprite[i], sf::Vector2f(width, height));
        mSprite[i].setPosition(0,0);
    }
    curChoose = 0;
}
void WalkingAnimal::ChangeState(int x){
    if (x==1) {
        if (curChoose != 2) curChoose = 2;
        else curChoose = 3;
    } else {
        if (curChoose != 0) curChoose = 0;
        else curChoose = 1;
    }
}

void WalkingAnimal::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite[curChoose], states);
    //draw hitbox
    sf::FloatRect rect = getHitbox();
    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1);
    shape.setPosition(rect.left, rect.top);
    target.draw(shape);
}

sf::FloatRect WalkingAnimal::getHitbox() const
{
    return getWorldTransform().transformRect(mSprite[curChoose].getGlobalBounds());
}

unsigned int WalkingAnimal::getCategory() const
{
    return Category::None;
}

