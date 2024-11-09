#include "object.hpp"
#include "object_defs.hpp"

#ifndef _AB_BLOCK_
#define _AB_BLOCK_

ObjectDefaults iceDefaults = {
    ObjectDefs::GetBodyDef(b2BodyType::b2_dynamicBody),
    b2CircleShape(),
    ObjectDefs::GetBoxShape(2, 2),
    1,
    50,
    ObjectDefs::GetRectSprite(64, 64, sf::Color::Blue)
};

ObjectDefaults woodDefaults = {
    ObjectDefs::GetBodyDef(b2BodyType::b2_dynamicBody),
    b2CircleShape(),
    ObjectDefs::GetBoxShape(2, 2),
    1,
    150,
    ObjectDefs::GetRectSprite(64, 64, sf::Color(142, 99, 23))
};

/**
 * @brief block that does not move and should not take damage
 * 
 */
ObjectDefaults fixedDefaults = {
    ObjectDefs::GetBodyDef(b2BodyType::b2_staticBody),
    b2CircleShape(),
    ObjectDefs::GetBoxShape(10, 2),
    0,
    -1,
    ObjectDefs::GetRectSprite(320, 64)
};

/**
 * @brief It's a block.
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
        sf::Sprite sprite,
        float hp = 100
    );

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
        ObjectDefaults* defaults,
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
    ObjectDefaults* defaults,
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
    return Block(world, x, y, &iceDefaults, width, height);
}

Block Block::GetWoodBlock(b2World* world, float x, float y, float width, float height)
{
    return Block(world, x, y, &woodDefaults, width, height);
}

Block Block::GetFixedBlock(b2World* world, float x, float y, float width, float height)
{
    return Block(world, x, y, &fixedDefaults, width, height);
}

#endif