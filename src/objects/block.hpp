#include "object.hpp"
#include "object_defs.hpp"
#include "../visual/texture_manager.hpp"

#ifndef OBJECT_BLOCK_HPP
#define OBJECT_BLOCK_HPP


using Defs = ObjectDefs::ObjectDefaults;

class Block : public Object{
public:
    Block(b2World* world, float x, float y, Defs* defaults) :
        Object(world, x, y, defaults) {
            isAnimated = false;
        }
    
    Block(){}  // for testing

};

namespace ObjectDefs{

    ObjectDefaults iceCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .normalTextures = {"IceCircleS"},
        .damageTextures = {"IceCircleSDamaged1", "IceCircleSDamaged2", "IceCircleSDamaged3"}
    };

    ObjectDefaults iceCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .normalTextures = {"IceCircleM"},
        .damageTextures = {"IceCircleMDamaged1", "IceCircleMDamaged2", "IceCircleMDamaged3"}
    };

    ObjectDefaults iceSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 1.05f, 1.05f),
        .spriteWidth = 1.05f * pixel_per_meter,
        .spriteHeight = 1.05f * pixel_per_meter,
        .normalTextures = {"IceSquare"},
        .damageTextures = {"IceSquareDamaged1", "IceSquareDamaged2", "IceSquareDamaged3"}
    };

    ObjectDefaults iceTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),  
        .density = 0.8f,
        .maxHp = CalculateHp(2.0f, 2.0f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"IceTriangleLeft"},
        .damageTextures = {"IceTriangleLeftDamaged1", "IceTriangleLeftDamaged2", "IceTriangleLeftDamaged3"}
    };

    ObjectDefaults iceTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),  
        .density = 0.8f,
        .maxHp = CalculateHp(2.0f, 2.0f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"IceTriangleRight"},
        .damageTextures = {"IceTriangleRightDamaged1", "IceTriangleRightDamaged2", "IceTriangleRightDamaged3"}
    };
  
    ObjectDefaults iceRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .normalTextures = {"IceRect"},
        .damageTextures = {"IceRectDamaged1", "IceRectDamaged2", "IceRectDamaged3"}
    };

    ObjectDefaults iceRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"IceRectS"},
        .damageTextures = {"IceRectSDamaged1", "IceRectSDamaged2", "IceRectSDamaged3"}
    };

    ObjectDefaults iceRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"IceRectM"},
        .damageTextures = {"IceRectMDamaged1", "IceRectMDamaged2", "IceRectMDamaged3"}
    };

    ObjectDefaults iceRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"IceRectL"},
        .damageTextures = {"IceRectLDamaged1", "IceRectLDamaged2", "IceRectLDamaged3"}
    };

    ObjectDefaults woodCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .normalTextures = {"WoodCircleS"},
        .damageTextures = {"WoodCircleSDamaged1", "WoodCircleSDamaged2", "WoodCircleSDamaged3"}
    };

    ObjectDefaults woodCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 *  pixel_per_meter,
        .normalTextures = {"WoodCircleM"},
        .damageTextures = {"WoodCircleMDamaged1", "WoodCircleMDamaged2", "WoodCircleMDamaged3"}
    };

    ObjectDefaults woodSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 1.05f),
        .spriteWidth = 1.05f * 2 * pixel_per_meter,
        .spriteHeight = 1.05f * 2 * pixel_per_meter,
        .normalTextures = {"WoodSquare"},
        .damageTextures = {"WoodSquareDamaged1", "WoodSquareDamaged2", "WoodSquareDamaged3"}
    };

    ObjectDefaults woodTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f * 2 * pixel_per_meter,
        .spriteHeight = 2.0f * 2 * pixel_per_meter,
        .normalTextures = {"WoodTriangleLeft"},
        .damageTextures = {"WoodTriangleLeftDamaged1", "WoodTriangleLeftDamaged2", "WoodTriangleLeftDamaged3"}
    };

    ObjectDefaults woodTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f * 2 * pixel_per_meter,
        .spriteHeight = 2.0f * 2 * pixel_per_meter,
        .normalTextures = {"WoodTriangleRight"},
        .damageTextures = {"WoodTriangleRightDamaged1", "WoodTriangleRightDamaged2", "WoodTriangleRightDamaged3"}
    };


    ObjectDefaults woodRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .normalTextures = {"WoodRect"},
        .damageTextures = {"WoodRectDamaged1", "WoodRectDamaged2", "WoodRectDamaged3"}
    };

    ObjectDefaults woodRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"WoodRectS"},
        .damageTextures = {"WoodRectSDamaged1", "WoodRectSDamaged2", "WoodRectSDamaged3"}
    };

    ObjectDefaults woodRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"WoodRectM"},
        .damageTextures = {"WoodRectMDamaged1", "WoodRectMDamaged2", "WoodRectMDamaged3"}
    };

    ObjectDefaults woodRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"WoodRectL"},
        .damageTextures = {"WoodRectLDamaged1", "WoodRectLDamaged2", "WoodRectLDamaged3"}
    };

    ObjectDefaults stoneCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .normalTextures = {"StoneCircleS"},
        .damageTextures = {"StoneCircleSDamaged1", "StoneCircleSDamaged2", "StoneCircleSDamaged3"}
    };

    ObjectDefaults stoneCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .normalTextures = {"StoneCircleM"},
        .damageTextures = {"StoneCircleMDamaged1", "StoneCircleMDamaged2", "StoneCircleMDamaged3"}
    };

    ObjectDefaults stoneSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 1.05f),
        .spriteWidth = 1.05f * 2 * pixel_per_meter,
        .spriteHeight = 1.05f * 2 * pixel_per_meter,
        .normalTextures = {"StoneSquare"},
        .damageTextures = {"StoneSquareDamaged1", "StoneSquareDamaged2", "StoneSquareDamaged3"}
    };

    ObjectDefaults stoneTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.0f),
        .spriteWidth = 2.0f  * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"StoneTriangleLeft"},
        .damageTextures = {"StoneTriangleLeftDamaged1", "StoneTriangleLeftDamaged2", "StoneTriangleLeftDamaged3"}
    };

    ObjectDefaults stoneTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.0f),
        .spriteWidth = 2.0f  * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"StoneTriangleRight"},
        .damageTextures = {"StoneTriangleRightDamaged1", "StoneTriangleRightDamaged2", "StoneTriangleRightDamaged3"}
    };

    ObjectDefaults stoneRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .normalTextures = {"StoneRect"},
        .damageTextures = {"StoneRectDamaged1", "StoneRectDamaged2", "StoneRectDamaged3"}
    };

    ObjectDefaults stoneRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectS"},
        .damageTextures = {"StoneRectSDamaged1", "StoneRectSDamaged2", "StoneRectSDamaged3"}
    };
    
    ObjectDefaults stoneRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectM"},
        .damageTextures = {"StoneRectMDamaged1", "StoneRectMDamaged2", "StoneRectMDamaged3"}
    };
    
    ObjectDefaults stoneRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectL"},
        .damageTextures = {"StoneRectLDamaged1", "StoneRectLDamaged2", "StoneRectLDamaged3"}
    };
}

#endif
