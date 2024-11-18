#include "object.hpp"
#include "object_defs.hpp"

#ifndef OBJECT_BLOCK_HPP
#define OBJECT_BLOCK_HPP

namespace BlockFactory
{
 ///////////////////////////////////////////////////////////////////////////////////
    /*ObjectDefs::ObjectDefaults iceDefaults = {
        GetBodyDef(b2BodyType::b2_dynamicBody),
        1,
        50,
        GetRectSprite(64, 64, sf::Color::Blue),
        b2CircleShape(),
        GetBoxShape(2, 2)
    };

    ObjectDefaults woodDefaults = {
        GetBodyDef(b2BodyType::b2_dynamicBody),
        1,
        100,
        GetRectSprite(64, 64, sf::Color(142, 99, 23)),
        b2CircleShape(),
        GetBoxShape(2, 2)
    };


    ObjectDefaults stoneDefaults = {
        GetBodyDef(b2BodyType::b2_dynamicBody),
        1,
        300,
        GetRectSprite(320, 64),
        b2CircleShape(),
        GetBoxShape(10, 2)
    };*/
///////////////////////////////////////////////////////////////////////////////////////////////////

    ObjectDefs::ObjectDefaults CreateIceDefaults(std::uniq* shape, float density = 0.8f, float hp = 50){
            ObjectDefs::ObjectDefaults defaults;

    }
    ObjectDefs::ObjectDefaults CreateWoodDefaults(b2Shape* shape, float density = 1.2f, float hp = 150);
    ObjectDefs::ObjectDefaults CreateStoneDefaults(b2Shape* shape, float density = 2.6f, float hp = 300);
    
   

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