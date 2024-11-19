#include "object.hpp"
#include "object_defs.hpp"
#include "visual/texture_manager.hpp"

#ifndef OBJECT_BLOCK_HPP
#define OBJECT_BLOCK_HPP

namespace ObjectDefs
{
 
    ObjectDefaults IceDefs() {
        ObjectDefaults ice;
        ice.bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody);
        ice.sprite = sf::Sprite();
        ice.shape = nullptr;
        ice.density = 0.8f;
        ice.hp = 50;
        return ice;
    }

    ObjectDefaults WoodDefs() {
        ObjectDefaults wood;
        wood.bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody);
        wood.sprite = sf::Sprite();
        wood.shape = nullptr;
        wood.density = 1.2f;
        wood.hp = 150;
        return wood;
    }

    ObjectDefaults StoneDefs() {
        ObjectDefaults stone;
        stone.bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody);
        stone.sprite = sf::Sprite();
        stone.shape = nullptr;
        stone.density = 2.6f;
        stone.hp = 300;
    }


    ObjectDefaults IceCircleDefs(float radius_m){
        ObjectDefaults ice = IceDefs();
        ice.shape = CreateShape(radius_m);
        ice.hp = CalculateHP(ice.hp, radius_m);
        float radius_pix = radius_m * ice.pixel_per_meter;
        ice.sprite = CreateSprite(radius_pix, radius_pix, TextureManager::getTexture("IceCircle"));
        return ice;
    }

    ObjectDefaults IceRectDefs(float width_m, float height_m) {
        ObjectDefaults ice = IceDefs();
        ice.shape = CreateShape(width_m, height_m);
        ice.hp = CalculateHP(ice.hp, width_m, height_m);
        float width_pix = width_m * ice.pixel_per_meter;
        float height_pix = height_m * ice.pixel_per_meter;
        ice.sprite = CreateSprite(width_pix, height_pix, TextureManager::getTexture("IceRect"));
        return ice;
    }

    ObjectDefaults WoodCircleDefs(float radius_m);
    ObjectDefaults WoodRectDefs(float width_m, float height_m);

    ObjectDefaults StoneCircleDefs(float radius_m);
    ObjectDefaults StoneRectDefs(float width_m, float height_m);

}

/**
 * @brief Physics block.
 * @brief No subclasses since blocks are functionally the same.
 * @brief Instead we have static variant getters.
 * 
 */
using Defs = ObjectDefs::ObjectDefaults;
class Block : public Object
{
public:
    Block(b2World* world, b2BodyDef* bodyDef, b2Shape* shape, float density,
          float x,float y, sf::Sprite sprite, float hp = 100);

    Block(){};

    Block(b2World* world,float x,float y,Defs* defaults);

    static Block GetIceCircle(b2World* world, float x, float y, float radius);
    static Block GetIceRect(b2World* world, float x, float y, float width, float height);

    static Block GetWoodCircle(b2World* world, float x, float y, float radius);
    static Block GetWoodRect(b2World* world, float x, float y, float width, float height);

    static Block GetStoneCircle(b2World* world, float x, float y, float radius);
    static Block GetStoneRect(b2World* world, float x, float y, float width, float height);
};


Block::Block(b2World* world, b2BodyDef* bodyDef, b2Shape* shape, float density,
            float x, float y, sf::Sprite sprite, float hp):
        Object(world, bodyDef, shape, density, x, y, sprite, hp){}

Block::Block(b2World* world, float x, float y, Defs* defs){
    defs->bodyDef.position.Set(x, y);
    body = world->CreateBody(&(defs->bodyDef));
    if (defs->shape){
        body->CreateFixture(defs->shape.get(), defs->density);
    }  
    hp = defs->hp;
    sprite = defs->sprite;
}

/////////////// Getter methods ///////////////////////////
Block Block::GetIceCircle(b2World* world, float x, float y, float radius_m){
    Defs iceDefs = ObjectDefs::IceCircleDefs(radius_m);
    return Block(world, x, y, &iceDefs);
}

Block Block::GetIceRect(b2World* world, float x, float y, float width_m, float height_m){
    Defs iceDefs = ObjectDefs::IceRectDefs(width_m, height_m);
    return Block(world, x, y, & iceDefs);
}

Block Block::GetWoodCircle(b2World* world, float x, float y, float radius_m){
    Defs woodDefs = ObjectDefs::WoodCircleDefs(radius_m);
    return Block(world, x, y, &woodDefs);
}
Block Block::GetWoodRect(b2World* world, float x, float y, float width_m, float height_m){
    Defs woodDefs = ObjectDefs::IceRectDefs(width_m, height_m);
    return Block(world, x, y, &woodDefs);
}

    
Block Block::GetStoneCircle(b2World* world, float x, float y, float radius_m){
    Defs stoneDefs = ObjectDefs::StoneCircleDefs(radius_m);
    return Block(world, x, y, &stoneDefs);    
}
Block Block::GetStoneRect(b2World* world, float x, float y, float width_m, float height_m){
    Defs stoneDefs = ObjectDefs::StoneRectDefs(width_m, height_m);
    return Block(world, x, y, &stoneDefs);
}

#endif