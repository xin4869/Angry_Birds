#include "object.hpp"
#include "object_defs.hpp"

#ifndef _AB_PIG_
#define _AB_PIG_

namespace ObjectDefs
{
    ObjectDefaults normalPigDefaults = {
        GetBodyDef(b2BodyType::b2_dynamicBody),
        GetCircleShape(1),
        b2PolygonShape(),
        1,
        50,
        GetRectSprite(32, 32, sf::Color::Green)
    };

    ObjectDefaults ironPigDefaults = {
        GetBodyDef(b2BodyType::b2_dynamicBody),
        GetCircleShape(1),
        b2PolygonShape(),
        1,
        150,
        GetRectSprite(32, 32, sf::Color(50, 50, 50))
    };
}

/**
 * @brief Pig class.
 * @brief No subclasses since pigs are functionally the same.
 * @brief Instead we have static variant getters.
 * 
 */
class Pig : public Object
{
public:
    Pig(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        sf::Sprite sprite,
        float hp = 100
    );

    /**
     * @brief Construct a new Pig object
     * 
     * @param defaults default values
     */
    Pig(
        b2World* world,
        float x,
        float y,
        ObjectDefs::ObjectDefaults* defaults
    );

    static Pig GetNormalPig(b2World* world, float x, float y);
    static Pig GetIronPig(b2World* world, float x, float y);
};

Pig::Pig(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        sf::Sprite sprite,
        float hp
) : Object(world, bodyDef, shape, density, x, y, sprite, hp)
{

}

Pig::Pig(
    b2World* world,
    float x,
    float y,
    ObjectDefs::ObjectDefaults* defaults
) : Object (
    world,
    &defaults->bodyDef,
    &defaults->circleShape,
    defaults->density,
    x, y,
    defaults->sprite,
    defaults->hp
)
{

}

Pig Pig::GetNormalPig(b2World* world, float x, float y)
{
    return Pig(world, x, y, &ObjectDefs::normalPigDefaults);
}

Pig Pig::GetIronPig(b2World* world, float x, float y)
{
    return Pig(world, x, y, &ObjectDefs::ironPigDefaults);
}

#endif
