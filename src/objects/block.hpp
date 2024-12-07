#include "object.hpp"
#include "object_defs.hpp"
#include "../visual/texture_manager.hpp"

#ifndef OBJECT_BLOCK_HPP
#define OBJECT_BLOCK_HPP


using Defs = ObjectDefs::ObjectDefaults;

class Block : public Object{
public:
    Block(b2World* world, float x, float y, Defs* defaults, float rotation=0.0f) :
        Object(world, x, y, defaults, rotation) {
            isAnimated = false;
            score = 50.0f;
        }
    
    Block(){}
    virtual bool TakeDamage(float dmg) {
        // Better way: sound lists for collision, damage, destroy
        bool isDead = CurrentHP <= 0;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
        bool isIce = sounds.size() == 8;

        if (CurrentHP <= 0) {
            if (isIce) playSound(rand() % 8);
            else playSound(8 + rand() % 3);
            if (!isDead) Destroy(2.0f);
        } else if (dmg > 10.0f) {
            if (isIce) playSound(rand() % 8);
            else playSound(5 + rand() % 3);
        } else if (dmg > 1.0f) {
            if (isIce) playSound(rand() % 8);
            else playSound(rand() % 5);
        }

        return CurrentHP <= 0;
    }
};

namespace ObjectDefs{
    std::vector<std::string> iceSoundNames = { "ice light collision a2", "ice light collision a1", "ice light collision a3", "ice light collision a4",
            "ice light collision a5", "ice light collision a6", "ice light collision a7", "ice light collision a8" };
    
    std::vector<std::string> woodSoundNames = { "wood collision a1", "wood collision a2", "wood collision a3", "wood collision a4",
            "wood collision a5", "wood damage a1", "wood damage a2", "wood damage a3",
            "wood destroyed a1", "wood destroyed a2", "wood destroyed a3", "wood rolling" };
    
    std::vector<std::string> rockSoundNames = { "rock collision a1", "rock collision a2", "rock collision a3", "rock collision a4",
            "rock collision a5", "rock damage a1", "rock damage a2", "rock damage a3",
            "rock destroyed a1", "rock destroyed a2", "rock destroyed a3", "rock rolling" };

    // ICE
    ObjectDefaults iceCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .normalTextures = {"IceCircleS"},
        .damageTextures = {"IceCircleSDamaged1", "IceCircleSDamaged2", "IceCircleSDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .normalTextures = {"IceCircleM"},
        .damageTextures = {"IceCircleMDamaged1", "IceCircleMDamaged2", "IceCircleMDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 1.05f, 1.05f),
        .spriteWidth = 1.05f * pixel_per_meter,
        .spriteHeight = 1.05f * pixel_per_meter,
        .normalTextures = {"IceSquare"},
        .damageTextures = {"IceSquareDamaged1", "IceSquareDamaged2", "IceSquareDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),  
        .density = 0.8f,
        .maxHp = CalculateHpTriangle(50.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"IceTriangleLeft"},
        .damageTextures = {"IceTriangleLeftDamaged1", "IceTriangleLeftDamaged2", "IceTriangleLeftDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"IceTriangleRight"},
        .damageTextures = {"IceTriangleRightDamaged1", "IceTriangleRightDamaged2", "IceTriangleRightDamaged3"},
        .soundNames = iceSoundNames
    };
  
    ObjectDefaults iceRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .normalTextures = {"IceRect"},
        .damageTextures = {"IceRectDamaged1", "IceRectDamaged2", "IceRectDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"IceRectS"},
        .damageTextures = {"IceRectSDamaged1", "IceRectSDamaged2", "IceRectSDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"IceRectM"},
        .damageTextures = {"IceRectMDamaged1", "IceRectMDamaged2", "IceRectMDamaged3"},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"IceRectL"},
        .damageTextures = {"IceRectLDamaged1", "IceRectLDamaged2", "IceRectLDamaged3"},
        .soundNames = iceSoundNames
    };

    // WOOD
    ObjectDefaults woodCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .normalTextures = {"WoodCircleS"},
        .damageTextures = {"WoodCircleSDamaged1", "WoodCircleSDamaged2", "WoodCircleSDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 *  pixel_per_meter,
        .normalTextures = {"WoodCircleM"},
        .damageTextures = {"WoodCircleMDamaged1", "WoodCircleMDamaged2", "WoodCircleMDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 1.05f, 1.05f),
        .spriteWidth = 1.05f * pixel_per_meter,
        .spriteHeight = 1.05f * pixel_per_meter,
        .normalTextures = {"WoodSquare"},
        .damageTextures = {"WoodSquareDamaged1", "WoodSquareDamaged2", "WoodSquareDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 1.2f,
        .maxHp = CalculateHpTriangle(150.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"WoodTriangleLeft"},
        .damageTextures = {"WoodTriangleLeftDamaged1", "WoodTriangleLeftDamaged2", "WoodTriangleLeftDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 1.2f,
        .maxHp = CalculateHpTriangle(150.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"WoodTriangleRight"},
        .damageTextures = {"WoodTriangleRightDamaged1", "WoodTriangleRightDamaged2", "WoodTriangleRightDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .normalTextures = {"WoodRect"},
        .damageTextures = {"WoodRectDamaged1", "WoodRectDamaged2", "WoodRectDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"WoodRectS"},
        .damageTextures = {"WoodRectSDamaged1", "WoodRectSDamaged2", "WoodRectSDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"WoodRectM"},
        .damageTextures = {"WoodRectMDamaged1", "WoodRectMDamaged2", "WoodRectMDamaged3"},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"WoodRectL"},
        .damageTextures = {"WoodRectLDamaged1", "WoodRectLDamaged2", "WoodRectLDamaged3"},
        .soundNames = woodSoundNames
    };

    // STONE
    ObjectDefaults stoneCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 0.53f),
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .normalTextures = {"StoneCircleS"},
        .damageTextures = {"StoneCircleSDamaged1", "StoneCircleSDamaged2", "StoneCircleSDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 1.0f),
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .normalTextures = {"StoneCircleM"},
        .damageTextures = {"StoneCircleMDamaged1", "StoneCircleMDamaged2", "StoneCircleMDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 1.05f, 1.05f),
        .spriteWidth = 1.05f * pixel_per_meter,
        .spriteHeight = 1.05f * pixel_per_meter,
        .normalTextures = {"StoneSquare"},
        .damageTextures = {"StoneSquareDamaged1", "StoneSquareDamaged2", "StoneSquareDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 2.6f,
        .maxHp = CalculateHpTriangle(300.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f  * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"StoneTriangleLeft"},
        .damageTextures = {"StoneTriangleLeftDamaged1", "StoneTriangleLeftDamaged2", "StoneTriangleLeftDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 2.6f,
        .maxHp = CalculateHpTriangle(300.0f, 2.0f, 2.0f),
        .spriteWidth = 2.0f  * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"StoneTriangleRight"},
        .damageTextures = {"StoneTriangleRightDamaged1", "StoneTriangleRightDamaged2", "StoneTriangleRightDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.3f, 1.3f),
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .normalTextures = {"StoneRect"},
        .damageTextures = {"StoneRectDamaged1", "StoneRectDamaged2", "StoneRectDamaged3"},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.0f, 0.55f),
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectS"},
        .damageTextures = {"StoneRectSDamaged1", "StoneRectSDamaged2", "StoneRectSDamaged3"},
        .soundNames = rockSoundNames
    };
    
    ObjectDefaults stoneRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 4.25f, 0.55f),
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectM"},
        .damageTextures = {"StoneRectMDamaged1", "StoneRectMDamaged2", "StoneRectMDamaged3"},
        .soundNames = rockSoundNames
    };
    
    ObjectDefaults stoneRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 5.075f, 0.55f),
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectL"},
        .damageTextures = {"StoneRectLDamaged1", "StoneRectLDamaged2", "StoneRectLDamaged3"},
        .soundNames = rockSoundNames
    };

    // FIXED
    ObjectDefaults fixedCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(0.53f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 0.53f * 2 * pixel_per_meter,
        .spriteHeight = 0.53f * 2 * pixel_per_meter,
        .normalTextures = {"StoneCircleS"}
    };

    ObjectDefaults fixedCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(1.0f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 1.0f * 2 * pixel_per_meter,
        .spriteHeight = 1.0f * 2 * pixel_per_meter,
        .normalTextures = {"StoneCircleM"}
    };

    ObjectDefaults fixedSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 1.05f * pixel_per_meter,
        .spriteHeight = 1.05f * pixel_per_meter,
        .normalTextures = {"StoneSquare"}
    };

    ObjectDefaults fixedTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 2.0f  * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"StoneTriangleLeft"}
    };

    ObjectDefaults fixedTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 2.0f  * pixel_per_meter,
        .spriteHeight = 2.0f * pixel_per_meter,
        .normalTextures = {"StoneTriangleRight"}
    };

    ObjectDefaults fixedRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 2.3f * pixel_per_meter,
        .spriteHeight = 1.3f * pixel_per_meter,
        .normalTextures = {"StoneRect"}
    };

    ObjectDefaults fixedRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 2.0f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectS"}
    };
    
    ObjectDefaults fixedRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 4.25f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectM"}
    };
    
    ObjectDefaults fixedRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        .normalTextures = {"StoneRectL"}
    };

    ObjectDefaults* getBlockDefaults(const std::string& name){
        if (name == "icecircles") return &iceCircleS;
        if (name == "icecirclem") return &iceCircleM;
        if (name == "icesquare") return &iceSquare;
        if (name == "icetriangleleft") return &iceTriangleLeft;
        if (name == "icetriangleright") return &iceTriangleRight;
        if (name == "icerect") return &iceRect;
        if (name == "icerects") return &iceRectS;
        if (name == "icerectm") return &iceRectM;
        if (name == "icerectl") return &iceRectL;
        if (name == "woodcircles") return &woodCircleS;
        if (name == "woodcirclem") return &woodCircleM;
        if (name == "woodsquare") return &woodSquare;
        if (name == "woodtriangleleft") return &woodTriangleLeft;
        if (name == "woodtriangleright") return &woodTriangleRight;
        if (name == "woodrect") return &woodRect;
        if (name == "woodrects") return &woodRectS;
        if (name == "woodrectm") return &woodRectM;
        if (name == "woodrectl") return &woodRectL;
        if (name == "stonecircles") return &stoneCircleS;
        if (name == "stonecirclem") return &stoneCircleM;
        if (name == "stonesquare") return &stoneSquare;
        if (name == "stonetriangleleft") return &stoneTriangleLeft;
        if (name == "stonetriangleright") return &stoneTriangleRight;
        if (name == "stonerect") return &stoneRect;
        if (name == "stonerects") return &stoneRectS;
        if (name == "stonerectm") return &stoneRectM;
        if (name == "stonerectl") return &stoneRectL;
        if (name == "fixedcircles") return &fixedCircleS;
        if (name == "fixedcirclem") return &fixedCircleM;
        if (name == "fixedsquare") return &fixedSquare;
        if (name == "fixedtriangleleft") return &fixedTriangleLeft;
        if (name == "fixedtriangleright") return &fixedTriangleRight;
        if (name == "fixedrect") return &fixedRect;
        if (name == "fixedrects") return &fixedRectS;
        if (name == "fixedrectm") return &fixedRectM;
        if (name == "fixedrectl") return &fixedRectL;
        return nullptr;
    }
}

#endif
