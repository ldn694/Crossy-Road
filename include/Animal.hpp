#pragma once

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Road.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Animal: public Entity {
    public:
        enum Type {
            Cat,
            Chicken,
            Lion,
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
                                Animal(Type type, std::string playerName, TextureHolder& textures, FontHolder& fonts, SceneNode* tmpNode, int& passedRoad);
        virtual unsigned int	getCategory() const;
        sf::FloatRect			getHitbox() const;
        void                    move(Direction direction);
        friend void             setZone(Animal* player, Zone* zone);
        void                    setMovementDuration(sf::Time duration);
    
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
        sf::Text                mPlayerNameText;
        Direction               mDirection;
        sf::Sprite				mSprite;
        sf::Time                mDuration;
        int&                    passedRoad;
};