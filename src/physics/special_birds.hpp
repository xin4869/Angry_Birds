#include "bird.hpp"
#include "object_defs.hpp"
#include <iostream>

#ifndef _AB_SPECIAL_BIRD_
#define _AB_SPECIAL_BIRD_

namespace ObjectDefs
{
    ObjectDefaults normalBirdDefaults = {
        GetBodyDef(b2BodyType::b2_dynamicBody),
        GetCircleShape(1),
        b2PolygonShape(),
        1,
        100,
        GetCircleSprite(32, 32, sf::Color(255, 0, 0))
    };
}

/**
 * @brief Physics bird with a special attack (not this one)
 * 
 */
class NormalBird : public Bird
{
public:
    NormalBird(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        sf::Sprite sprite,
        float hp=100
    );

    /**
     * @brief Construct a new Normal Bird. Uses default values.
     */
    NormalBird(
        b2World* world,
        float x=0,
        float y=0
    );

    void Attack();
};

NormalBird::NormalBird(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        sf::Sprite sprite,
        float hp
    ) : Bird(world, bodyDef, shape, density, x, y, sprite, hp)
{

}

NormalBird::NormalBird(
        b2World* world,
        float x,
        float y
    ) : Bird(
        world,
        &ObjectDefs::normalBirdDefaults.bodyDef,
        &ObjectDefs::normalBirdDefaults.circleShape,
        ObjectDefs::normalBirdDefaults.density,
        x, y,
        ObjectDefs::normalBirdDefaults.sprite,
        ObjectDefs::normalBirdDefaults.hp)
{

}

void NormalBird::Attack()
{
    std::cout << "Bird Attacked" << std::endl;
}

#endif
