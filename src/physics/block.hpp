#include "object.hpp"
#include "object_defs.hpp"

#ifndef _AB_BLOCK_
#define _AB_BLOCK_

namespace ObjectDefs
{
    ObjectDefaults iceDefaults = {
        GetBodyDef(b2BodyType::b2_dynamicBody),
        b2CircleShape(),
        GetBoxShape(2, 2),
        1,
        50,
        GetRectSprite(64, 64, sf::Color::Blue)
    };

    ObjectDefaults woodDefaults = {
        GetBodyDef(b2BodyType::b2_dynamicBody),
        b2CircleShape(),
        GetBoxShape(2, 2),
        1,
        150,
        GetRectSprite(64, 64, sf::Color(142, 99, 23))
    };

    /**
     * @brief block that does not move and should not take damage
     * 
     */
    ObjectDefaults fixedDefaults = {
        GetBodyDef(b2BodyType::b2_staticBody),
        b2CircleShape(),
        GetBoxShape(10, 2),
        0,
        -1,
        GetRectSprite(320, 64)
    };
}

/**
 * @brief Physics block.
 * @brief No subclasses since blocks are functionally the same.
 * @brief Instead we have static variant getters.
 * 
 */
class Block : public Object
{
public:
    Block(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        sf::Sprite sprite=ObjectDefs::GetRectSprite(32, 32),
        float hp = 100
    );
    Block(){};

    /**
     * @brief Construct a new Block object
     * 
     * @param defaults default values
     * @param width uses this if defined
     * @param height uses this if defined
     */
    Block(
        b2World* world,
        float x,
        float y,
        ObjectDefs::ObjectDefaults* defaults,
        float width=0,
        float height=0
    );

    static Block GetIceBlock(b2World* world, float x, float y, float width, float height);
    static Block GetWoodBlock(b2World* world, float x, float y, float width, float height);
    static Block GetFixedBlock(b2World* world, float x, float y, float width, float height);
};

Block::Block(
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

Block::Block(
    b2World* world,
    float x,
    float y,
    ObjectDefs::ObjectDefaults* defaults,
    float width,
    float height
)
{
    defaults->bodyDef.position.Set(x, y);
    body = world->CreateBody(&(defaults->bodyDef));
    if (width > 0 && height > 0)
    {
        b2PolygonShape box = ObjectDefs::GetBoxShape(width, height);
        body->CreateFixture(&box, defaults->density);
    } else
    {
        body->CreateFixture(&(defaults->boxShape), defaults->density);
    }
    hp = defaults->hp;
    sprite = defaults->sprite;
}

Block Block::GetIceBlock(b2World* world, float x, float y, float width, float height)
{
    return Block(world, x, y, &ObjectDefs::iceDefaults, width, height);
}

Block Block::GetWoodBlock(b2World* world, float x, float y, float width, float height)
{
    return Block(world, x, y, &ObjectDefs::woodDefaults, width, height);
}

Block Block::GetFixedBlock(b2World* world, float x, float y, float width, float height)
{
    return Block(world, x, y, &ObjectDefs::fixedDefaults, width, height);
}

#endif