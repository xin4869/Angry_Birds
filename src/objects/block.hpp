#include "object.hpp"
#include "object_defs.hpp"
#include "visual/texture_manager.hpp"

#ifndef OBJECT_BLOCK_HPP
#define OBJECT_BLOCK_HPP


using Defs = ObjectDefs::ObjectDefaults;

class Block : public Object{
public:
    Block(b2World* world, float x, float y, Defs* defs):
        Object(world, &(defs->bodyDef), defs->shape.get(),defs->density,x, y, 
        defs->spriteWidth, defs->spriteHeight, defs->textureNames, defs->maxHp) {}

private:

    Block(b2World* world, b2BodyDef* bodyDef, b2Shape* shape, float density,float x,
         float y, float spriteWidth, float spriteHeight, std::vector<std::string> textures, float hp):
        Object(world, bodyDef, shape, density, x, y, spriteWidth, spriteHeight, textures, hp) {}

    Block(){};

};

namespace ObjectDefs{

    ObjectDefaults iceCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),  
        .density = 0.8f,
        .maxHp = CalculateHP(50.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .textureNames = {"IceCircleS","IceCircleSDamaged1", "IceCircleSDamaged2", "IceCircleSDamaged3"}
    };

    ObjectDefaults iceCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),  
        .density = 0.8f,
        .maxHp = CalculateHP(50.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .textureNames = {"IceCircleM","IceCircleMDamaged1", "IceCircleMDamaged2", "IceCircleMDamaged3"}
    };

    ObjectDefaults iceSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 0.8f,
        .maxHp = CalculateHP(50.0f, 1.05f, 1.05f),
        .spriteWidth = 1.05f * pixel_per_meter,
        .spriteHeight = 1.05f * pixel_per_meter,
        .textureNames = {"IceSquare", "IceSquareDamaged1", "IceSquareDamaged2", "IceSquareDamaged3"}
    };
  
    ObjectDefaults iceRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 0.8f,
        .maxHp = CalculateHP(50.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .textureNames = {"IceRect", "IceRectDamaged1", "IceRectDamaged2", "IceRectDamaged3"}
    };

    ObjectDefaults iceRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHP(50.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"IceRectS", "IceRectSDamaged1", "IceRectSDamaged2", "IceRectSDamaged3"}
    };

    ObjectDefaults iceRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHP(50.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"IceRectM", "IceRectMDamaged1", "IceRectMDamaged2", "IceRectMDamaged3"}
    };

    ObjectDefaults iceRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHP(50.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"IceRectL", "IceRectLDamaged1", "IceRectLDamaged2", "IceRectLDamaged3"}
    };

    ObjectDefaults woodCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 1.2f,
        .maxHp = CalculateHP(150.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .textureNames = {"WoodCircleS","WoodCircleSDamaged1", "WoodCircleSDamaged2", "WoodCircleSDamaged3"}
    };

    ObjectDefaults woodCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.2f,
        .maxHp = CalculateHP(150.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 *  pixel_per_meter,
        .textureNames = {"WoodCircleM","WoodCircleMDamaged1", "WoodCircleMDamaged2", "WoodCircleMDamaged3"}
    };

    ObjectDefaults woodSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f),
        .density = 1.2f,
        .maxHp = CalculateHP(150.0f, 1.05f),
        .spriteWidth = 1.05f * 2 * pixel_per_meter,
        .spriteHeight = 1.05f * 2 * pixel_per_meter,
        .textureNames = {"WoodSquare","WoodSquareDamaged1", "WoodSquareDamaged2", "WoodSquareDamaged3"}
    };

    ObjectDefaults woodRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 1.2f,
        .maxHp = CalculateHP(150.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .textureNames = {"WoodRect","WoodRectDamaged1", "WoodRectDamaged2", "WoodRectDamaged3"}
    };

    ObjectDefaults woodRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHP(150.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"WoodRectS","WoodRectSDamaged1", "WoodRectSDamaged2", "WoodRectSDamaged3"}
    };

    ObjectDefaults woodRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHP(150.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"WoodRectM","WoodRectMDamaged1", "WoodRectMDamaged2", "WoodRectMDamaged3"}
    };

    ObjectDefaults woodRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHP(150.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"WoodRectL","WoodRectLDamaged1", "WoodRectLDamaged2", "WoodRectLDamaged3"}
    };

    ObjectDefaults stoneCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 2.6f,
        .maxHp = CalculateHP(300.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .textureNames = {"StoneCircleS","StoneCircleSDamaged1", "StoneCircleSDamaged2", "StoneCircleSDamaged3"}
    };

    ObjectDefaults stoneCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 2.6f,
        .maxHp = CalculateHP(300.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .textureNames = {"StoneCircleM","StoneCircleMDamaged1", "StoneCircleMDamaged2", "StoneCircleMDamaged3"}
    };

    ObjectDefaults stoneRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 2.6f,
        .maxHp = CalculateHP(300.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .textureNames = {"StoneRect","StoneRectDamaged1", "StoneRectDamaged2", "StoneRectDamaged3"}
    };

    ObjectDefaults stoneRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHP(300.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"StoneRectS","StoneRectSDamaged1", "StoneRectSDamaged2", "StoneRectSDamaged3"}
    };
    
    ObjectDefaults stoneRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHP(300.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"StoneRectM","StoneRectMDamaged1", "StoneRectMDamaged2", "StoneRectMDamaged3"}
    };
    
    ObjectDefaults stoneRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHP(300.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"StoneRectL","StoneRectLDamaged1", "StoneRectLDamaged2", "StoneRectLDamaged3"}
    };
}

#endif
