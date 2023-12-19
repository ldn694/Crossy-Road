#pragma once

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Animal: public Entity {
    public:
        enum Type {
            Cat,
            Chicken,
            Zebra,
            Pig,
            Fox,
            NumAnimalTypes
        };
        enum Direction {
            Left,
            Right,
            Up,
            Down,
            NumDirections
        };

    public:
                                Animal(Type type, TextureHolder& textures);
        virtual unsigned int	getCategory() const;
        sf::FloatRect			getHitbox() const;
        void                    move(Direction direction);
    
    private:
        void                    changeDirection(Direction direction);
        virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        Textures::ID            toTextureID(Type type, Direction direction);
    
    private:
        TextureHolder&          mTextures;
        Type					mType;
        Direction               mDirection;
        sf::Sprite				mSprite;
};