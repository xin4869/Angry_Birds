#include "object.hpp"
#include "object_defs.hpp"
#include "../visual/texture_manager.hpp"

#ifndef OBJECT_BLOCK_HPP
#define OBJECT_BLOCK_HPP


using Defs = ObjectDefs::ObjectDefaults;

class Block : public Object{
public:
    Block(b2World* world, float x, float y, Defs* defaults) :
        Object(world, x, y, defaults) {}
    
    Block(){}  // for testing
};

namespace ObjectDefs{
    std::vector<std::string> iceSoundNames = { "ice light collision a2", "ice light collision a1", "ice light collision a3", "ice light collision a4",
            "ice light collision a5", "ice light collision a6", "ice light collision a7", "ice light collision a8" };
    
    std::vector<std::string> woodSoundNames = { "wood collision a1", "wood collision a2", "wood collision a3", "wood collision a4",
            "wood collision a5", "wood collision a6", "wood damage a1", "wood damage a2", "wood damage a3",
            "wood destroyed a1", "wood destroyed a2", "wood destroyed a3", "wood rolling" };
    
    std::vector<std::string> rockSoundNames = { "rock collision a1", "rock collision a2", "rock collision a3", "rock collision a4",
            "rock collision a5", "rock damage a1", "rock damage a2", "rock damage a3",
            "rock destroyed a1", "rock destroyed a2", "rock destroyed a3", "rock rolling" };

    ObjectDefaults iceCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .textureNames = {"IceCircleS","IceCircleSDamaged1", "IceCircleSDamaged2", "IceCircleSDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .textureNames = {"IceCircleM","IceCircleMDamaged1", "IceCircleMDamaged2", "IceCircleMDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 1.05f, 1.05f),
        .spriteWidth = 1.05f * pixel_per_meter,
        .spriteHeight = 1.05f * pixel_per_meter,
        .textureNames = {"IceSquare", "IceSquareDamaged1", "IceSquareDamaged2", "IceSquareDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),  
        .density = 0.8f,
        .maxHp = CalculateHp(2.0f, 2.0f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .textureNames = {"IceTriangleLeft", "IceTriangleLeftDamaged1", "IceTriangleLeftDamaged2", "IceTriangleLeftDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),  
        .density = 0.8f,
        .maxHp = CalculateHp(2.0f, 2.0f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .textureNames = {"IceTriangleRight", "IceTriangleRightDamaged1", "IceTriangleRightDamaged2", "IceTriangleRightDamaged3"},
        .soundNames = iceSoundNames
    };
  
    ObjectDefaults iceRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .textureNames = {"IceRect", "IceRectDamaged1", "IceRectDamaged2", "IceRectDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"IceRectS", "IceRectSDamaged1", "IceRectSDamaged2", "IceRectSDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"IceRectM", "IceRectMDamaged1", "IceRectMDamaged2", "IceRectMDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"IceRectL", "IceRectLDamaged1", "IceRectLDamaged2", "IceRectLDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults woodCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .textureNames = {"WoodCircleS","WoodCircleSDamaged1", "WoodCircleSDamaged2", "WoodCircleSDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 *  pixel_per_meter,
        .textureNames = {"WoodCircleM","WoodCircleMDamaged1", "WoodCircleMDamaged2", "WoodCircleMDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 1.05f),
        .spriteWidth = 1.05f * 2 * pixel_per_meter,
        .spriteHeight = 1.05f * 2 * pixel_per_meter,
        .textureNames = {"WoodSquare","WoodSquareDamaged1", "WoodSquareDamaged2", "WoodSquareDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f * 2 * pixel_per_meter,
        .spriteHeight = 2.0f * 2 * pixel_per_meter,
        .textureNames = {"WoodTriangleLeft","WoodTriangleLeftDamaged1", "WoodTriangleLeftDamaged2", "WoodTriangleLeftDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f * 2 * pixel_per_meter,
        .spriteHeight = 2.0f * 2 * pixel_per_meter,
        .textureNames = {"WoodTriangleRight","WoodTriangleRightDamaged1", "WoodTriangleRightDamaged2", "WoodTriangleRightDamaged3"},
        .soundNames = woodSoundNames
    };


    ObjectDefaults woodRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .textureNames = {"WoodRect","WoodRectDamaged1", "WoodRectDamaged2", "WoodRectDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"WoodRectS","WoodRectSDamaged1", "WoodRectSDamaged2", "WoodRectSDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"WoodRectM","WoodRectMDamaged1", "WoodRectMDamaged2", "WoodRectMDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"WoodRectL","WoodRectLDamaged1", "WoodRectLDamaged2", "WoodRectLDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults stoneCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .textureNames = {"StoneCircleS","StoneCircleSDamaged1", "StoneCircleSDamaged2", "StoneCircleSDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .textureNames = {"StoneCircleM","StoneCircleMDamaged1", "StoneCircleMDamaged2", "StoneCircleMDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 1.05f),
        .spriteWidth = 1.05f * 2 * pixel_per_meter,
        .spriteHeight = 1.05f * 2 * pixel_per_meter,
        .textureNames = {"StoneSquare","StoneSquareDamaged1", "StoneSquareDamaged2", "StoneSquareDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.0f),
        .spriteWidth = 2.0f  * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .textureNames = {"StoneTriangleLeft","StoneTriangleLeftDamaged1", "StoneTriangleLeftDamaged2", "StoneTriangleLeftDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.0f),
        .spriteWidth = 2.0f  * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .textureNames = {"StoneTriangleRight","StoneTriangleRightDamaged1", "StoneTriangleRightDamaged2", "StoneTriangleRightDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .textureNames = {"StoneRect","StoneRectDamaged1", "StoneRectDamaged2", "StoneRectDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"StoneRectS","StoneRectSDamaged1", "StoneRectSDamaged2", "StoneRectSDamaged3"},
        .soundNames = rockSoundNames
    };
    
    ObjectDefaults stoneRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"StoneRectM","StoneRectMDamaged1", "StoneRectMDamaged2", "StoneRectMDamaged3"},
        .soundNames = rockSoundNames
    };
    
    ObjectDefaults stoneRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .textureNames = {"StoneRectL","StoneRectLDamaged1", "StoneRectLDamaged2", "StoneRectLDamaged3"},
        .soundNames = rockSoundNames
    };
}

#endif
