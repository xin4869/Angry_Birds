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
    virtual bool TakeDamage(float dmg) override {
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

        if (!isDamaged) {isDamaged = true;}
        
        return CurrentHP <= 0;
    }
    
    virtual void updateTexture(float deltaTime) override {
        animationTimer += deltaTime;
        if (animationTimer > 0.1f) {
            if (isDamaged) {
                animationTimer = 0.f;
                size_t idx = static_cast<size_t>((damageTextures.size() - 1) * (1 - CurrentHP/MaxHP));              
                idx = std::min(idx, damageTextures.size() - 1);
                this->sprite.setTexture(TextureManager::getTexture(damageTextures[idx].first));
            }   
        }              
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
        .normalTextures = {{"IceCircleS", 0.f}},
        .damageTextures = {{"IceCircleSDamaged1",0.f}, {"IceCircleSDamaged2",0.f}, {"IceCircleSDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 1.0f),
        .normalTextures = {{"IceCircleM",0.f}},
        .damageTextures = {{"IceCircleMDamaged1",0.f}, {"IceCircleMDamaged2", 0.f}, {"IceCircleMDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 1.05f, 1.05f),
        .normalTextures = {{"IceSquare", 0.f}},
        .damageTextures = {{"IceSquareDamaged1",0.f}, {"IceSquareDamaged2", 0.f}, {"IceSquareDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),  
        .density = 0.8f,
        .maxHp = CalculateHpTriangle(50.0f, 2.0f, 2.0f),
        .normalTextures = {{"IceTriangleLeft", 0.f}},
        .damageTextures = {{"IceTriangleLeftDamaged1",0.f}, {"IceTriangleLeftDamaged2", 0.f}, {"IceTriangleLeftDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),  
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.0f, 2.0f),
        .normalTextures = {{"IceTriangleRight", 0.f}},
        .damageTextures = {{"IceTriangleRightDamaged1",0.f}, {"IceTriangleRightDamaged2", 0.f}, {"IceTriangleRightDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };
  
    ObjectDefaults iceRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.3f, 1.3f),
        .normalTextures = {{"IceRect", 0.f}},
        .damageTextures = {{"IceRectDamaged1",0.f}, {"IceRectDamaged2", 0.f}, {"IceRectDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 2.0f, 0.55f),
        .normalTextures = {{"IceRectS", 0.f}},
        .damageTextures = {{"IceRectSDamaged1",0.f}, {"IceRectSDamaged2", 0.f}, {"IceRectSDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 4.25f, 0.55f),
        .normalTextures = {{"IceRectM", 0.f}},
        .damageTextures = {{"IceRectMDamaged1",0.f}, {"IceRectMDamaged2", 0.f}, {"IceRectMDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };

    ObjectDefaults iceRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 0.8f,
        .maxHp = CalculateHp(50.0f, 5.075f, 0.55f),
        .normalTextures = {{"IceRectL", 0.f}},
        .damageTextures = {{"IceRectLDamaged1",0.f}, {"IceRectLDamaged2", 0.f}, {"IceRectLDamaged3", 0.f}},
        .soundNames = iceSoundNames
    };

    // WOOD
    ObjectDefaults woodCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 0.53f),
        .normalTextures = {{"WoodCircleS", 0.f}},
        .damageTextures = {{"WoodCircleSDamaged1",0.f}, {"WoodCircleSDamaged2", 0.f}, {"WoodCircleSDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 1.0f),
        .normalTextures = {{"WoodCircleM", 0.f}},
        .damageTextures = {{"WoodCircleMDamaged1",0.f}, {"WoodCircleMDamaged2", 0.f}, {"WoodCircleMDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 1.05f, 1.05f),
        .normalTextures = {{"WoodSquare", 0.f}},
        .damageTextures = {{"WoodSquareDamaged1",0.f}, {"WoodSquareDamaged2", 0.f}, {"WoodSquareDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 1.2f,
        .maxHp = CalculateHpTriangle(150.0f, 2.0f, 2.0f),
        .normalTextures = {{"WoodTriangleLeft", 0.f}},
        .damageTextures = {{"WoodTriangleLeftDamaged1",0.f}, {"WoodTriangleLeftDamaged2", 0.f}, {"WoodTriangleLeftDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 1.2f,
        .maxHp = CalculateHpTriangle(150.0f, 2.0f, 2.0f),
        .normalTextures = {{"WoodTriangleRight", 0.f}},
        .damageTextures = {{"WoodTriangleRightDamaged1",0.f}, {"WoodTriangleRightDamaged2", 0.f}, {"WoodTriangleRightDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.3f, 1.3f),
        .normalTextures = {{"WoodRect", 0.f}},
        .damageTextures = {{"WoodRectDamaged1",0.f}, {"WoodRectDamaged2", 0.f}, {"WoodRectDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 2.0f, 0.55f),
        .normalTextures = {{"WoodRectS", 0.f}},
        .damageTextures = {{"WoodRectSDamaged1",0.f}, {"WoodRectSDamaged2", 0.f}, {"WoodRectSDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 4.25f, 0.55f),
        .normalTextures = {{"WoodRectM", 0.f}},
        .damageTextures = {{"WoodRectMDamaged1",0.f}, {"WoodRectMDamaged2", 0.f}, {"WoodRectMDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    ObjectDefaults woodRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 1.2f,
        .maxHp = CalculateHp(150.0f, 5.075f, 0.55f),
        .normalTextures = {{"WoodRectL", 0.f}},
        .damageTextures = {{"WoodRectLDamaged1",0.f}, {"WoodRectLDamaged2", 0.f}, {"WoodRectLDamaged3", 0.f}},
        .soundNames = woodSoundNames
    };

    // STONE
    ObjectDefaults stoneCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(0.53f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 0.53f),
        .normalTextures = {{"StoneCircleS", 0.f}},
        .damageTextures = {{"StoneCircleSDamaged1",0.f}, {"StoneCircleSDamaged2", 0.f}, {"StoneCircleSDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 1.0f),
        .normalTextures = {{"StoneCircleM", 0.f}},
        .damageTextures = {{"StoneCircleMDamaged1",0.f}, {"StoneCircleMDamaged2", 0.f}, {"StoneCircleMDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 1.05f, 1.05f),
        .normalTextures = {{"StoneSquare", 0.f}},
        .damageTextures = {{"StoneSquareDamaged1",0.f}, {"StoneSquareDamaged2", 0.f}, {"StoneSquareDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 2.6f,
        .maxHp = CalculateHpTriangle(300.0f, 2.0f, 2.0f),
        .normalTextures = {{"StoneTriangleLeft", 0.f}},
        .damageTextures = {{"StoneTriangleLeftDamaged1", 0.f}, {"StoneTriangleLeftDamaged2", 0.f}, {"StoneTriangleLeftDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 2.6f,
        .maxHp = CalculateHpTriangle(300.0f, 2.0f, 2.0f),
        .normalTextures = {{"StoneTriangleRight", 0.f}},
        .damageTextures = {{"StoneTriangleRightDamaged1", 0.f}, {"StoneTriangleRightDamaged2", 0.f}, {"StoneTriangleRightDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.3f, 1.3f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.3f, 1.3f),
        .normalTextures = {{"StoneRect", 0.f}},
        .damageTextures = {{"StoneRectDamaged1", 0.f}, {"StoneRectDamaged2", 0.f}, {"StoneRectDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };

    ObjectDefaults stoneRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(2.0f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 2.0f, 0.55f),
        .normalTextures = {{"StoneRectS", 0.f}},
        .damageTextures = {{"StoneRectSDamaged1", 0.f}, {"StoneRectSDamaged2", 0.f}, {"StoneRectSDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };
    
    ObjectDefaults stoneRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(4.25f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 4.25f, 0.55f),
        .normalTextures = {{"StoneRectM", 0.f}},
        .damageTextures = {{"StoneRectMDamaged1", 0.f}, {"StoneRectMDamaged2", 0.f}, {"StoneRectMDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };
    
    ObjectDefaults stoneRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 2.6f,
        .maxHp = CalculateHp(300.0f, 5.075f, 0.55f),
        .normalTextures = {{"StoneRectL", 0.f}},
        .damageTextures = {{"StoneRectLDamaged1", 0.f}, {"StoneRectLDamaged2", 0.f}, {"StoneRectLDamaged3", 0.f}},
        .soundNames = rockSoundNames
    };

    // FIXED
    ObjectDefaults fixedCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(0.53f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneCircleS", 0.f}}
    };

    ObjectDefaults fixedCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(1.0f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneCircleM", 0.f}}
    };

    ObjectDefaults fixedSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(1.05f, 1.05f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneSquare", 0.f}}
    };

    ObjectDefaults fixedTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, true),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneTriangleLeft", 0.f}}
    };

    ObjectDefaults fixedTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShapeTriangle(2.0f, 2.0f, false),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneTriangleRight", 0.f}}
    };
    
    ObjectDefaults fixedRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(5.075f, 0.55f),
        .density = 0.0f,
        .maxHp = FLT_MAX,
        .spriteWidth = 5.075f * pixel_per_meter,
        .spriteHeight = 0.55f * pixel_per_meter,
        //.normalTextures = {"StoneRectL"}
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
        if (name == "fixedrectl") return &fixedRectL;
        return nullptr;
    }
}

#endif
