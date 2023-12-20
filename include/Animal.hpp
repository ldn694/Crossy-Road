#pragma once

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

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
                                Animal(Type type, TextureHolder& textures, SceneNode* tmpNode);
        virtual unsigned int	getCategory() const;
        sf::FloatRect			getHitbox() const;
        void                    move(Direction direction);
        friend void             setZone(Animal* player, Zone* zone);
    
    private:
        virtual void            updateCurrent(sf::Time dt);
        void                    changeDirection(Direction direction);
        virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        Textures::ID            toTextureID(Type type, Direction direction);
        bool                    addAnimalAnimation(Zone* zone, sf::Time duration, sf::Vector2f offset = sf::Vector2f(0, 0));
        Zone*                   mZone;
        Zone*                   mNextZone;
        SceneNode*              tmpNode;
        bool                    isMoving = false;
        sf::Vector2f            mOldPosition;
        sf::Vector2f            mTmpOldPosition;
    
    private:
        TextureHolder&          mTextures;
        Type					mType;
        Direction               mDirection;
        sf::Sprite				mSprite;
};