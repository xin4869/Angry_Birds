#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "object_defs.hpp"

#ifndef _AB_OBJECT_
#define _AB_OBJECT_

/**
 * @brief Represents a basic physics object. Might make this abstract later.
 * 
 */
class Object
{
public:
    float hp;
    b2Body* body;
    sf::Sprite sprite;

    /**
     * @brief Construct a new Object
     * 
     * @param world world to add in
     * @param bodyDef defines body (type, position, rotation)
     * @param shape defines shape (hitbox)
     * @param density 
     * @param x coordinate
     * @param y coordinate
     * @param sprite object sprite
     * @param hp hitpoints
     */
    Object(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        sf::Sprite sprite=ObjectDefs::GetRectSprite(32, 32),
        float hp = 100
    );
    Object(){};
    ~Object(){};
    void TakeDamage(float dmg){ std::cout << "Took " << dmg << " dmg" << std::endl; };

    /**
     * @brief Destroy when hp <= 0 (e.g.)
     * 
     */
    void Destroy(){};
};

Object::Object(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        sf::Sprite sprite,
        float hp
    ) : hp(hp), sprite(sprite)
{
    bodyDef->position.Set(x, y);
    body = world->CreateBody(bodyDef);
    body->CreateFixture(shape, density);
}

#endif
