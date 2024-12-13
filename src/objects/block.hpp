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
            score = 50.0f;
        }
    
    Block(){}

    virtual bool TakeDamage(float dmg) override {
        if (MaxHP == FLT_MAX) return false;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
 
        if (CurrentHP <= 0) {
            playSound(soundType::destroy);
            Destroy(2.0f);
        } else if (dmg > 30.0f) {
            playSound(soundType::damage);
        } else if (dmg > 1.0f) {
            playSound(soundType::collision);
        }
        
        return CurrentHP <= 0;
    }

 
    virtual void updateTexture(float deltaTime) override {
        float hp_percent = CurrentHP / MaxHP; 
        if (hp_percent > 0.7f) {
            sprite.setTexture(TextureManager::getTexture(normalTextures[0].first));
        } else if (0.4f< hp_percent && hp_percent <= 0.7f) {
            sprite.setTexture(TextureManager::getTexture(damageTextures[0].first));
        } else if (0.2f< hp_percent && hp_percent <=0.4f) {
            sprite.setTexture(TextureManager::getTexture(damageTextures[1].first));         
        } else {
            sprite.setTexture(TextureManager::getTexture(damageTextures[2].first));
        }
    }
};

namespace ObjectDefs{
    // SHAPES
    const float circleSRadius = 0.53f;
    const float circleMRadius = 1.0f;
    const float squareSize = 1.05f;
    const float triangleSize = 2.0f;
    const float rectWidth = 2.3f;
    const float rectHeight = 1.3f;
    const float rectXHeight = 0.55f;
    const float rectSWidth = 2.0f;
    const float rectMWidth = 4.25f;
    const float rectLWidth = 5.075f;

    // ICE
    std::vector<std::string> iceCollisionSoundNames = { "ice light collision a1", "ice light collision a2", "ice light collision a3", "ice light collision a4" };
    std::vector<std::string> iceDamageSoundNames = { "ice light collision a5", "ice light collision a6" };
    std::vector<std::string> iceDestroySoundNames = { "ice light collision a7", "ice light collision a8" };
    
    const float iceDensity = 0.8f;
    const float iceBaseHP = 50.0f;

    ObjectDefaults iceCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(circleSRadius),
        .density = iceDensity,
        .maxHp = CalculateHp(iceBaseHP, circleSRadius),
        .normalTextures = {{"IceCircleS", 0.f}},
        .damageTextures = {{"IceCircleSDamaged1",0.f}, {"IceCircleSDamaged2",0.f}, {"IceCircleSDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };

    ObjectDefaults iceCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(circleMRadius),  
        .density = iceDensity,
        .maxHp = CalculateHp(iceBaseHP, circleMRadius),
        .normalTextures = {{"IceCircleM",0.f}},
        .damageTextures = {{"IceCircleMDamaged1",0.f}, {"IceCircleMDamaged2", 0.f}, {"IceCircleMDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };

    ObjectDefaults iceSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(squareSize, squareSize),
        .density = iceDensity,
        .maxHp = CalculateHp(iceBaseHP, squareSize, squareSize),
        .normalTextures = {{"IceSquare", 0.f}},
        .damageTextures = {{"IceSquareDamaged1",0.f}, {"IceSquareDamaged2", 0.f}, {"IceSquareDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };

    ObjectDefaults iceTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(triangleSize, triangleSize, true),
        .density = iceDensity,
        .maxHp = CalculateHpTriangle(iceBaseHP, triangleSize, triangleSize),
        .normalTextures = {{"IceTriangleLeft", 0.f}},
        .damageTextures = {{"IceTriangleLeftDamaged1",0.f}, {"IceTriangleLeftDamaged2", 0.f}, {"IceTriangleLeftDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };

    ObjectDefaults iceTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(triangleSize, triangleSize, false),  
        .density = iceDensity,
        .maxHp = CalculateHpTriangle(iceBaseHP, triangleSize, triangleSize),
        .normalTextures = {{"IceTriangleRight", 0.f}},
        .damageTextures = {{"IceTriangleRightDamaged1",0.f}, {"IceTriangleRightDamaged2", 0.f}, {"IceTriangleRightDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };
  
    ObjectDefaults iceRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectWidth, rectHeight),
        .density = iceDensity,
        .maxHp = CalculateHp(iceBaseHP, rectWidth, rectHeight),
        .normalTextures = {{"IceRect", 0.f}},
        .damageTextures = {{"IceRectDamaged1",0.f}, {"IceRectDamaged2", 0.f}, {"IceRectDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };

    ObjectDefaults iceRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectSWidth, rectXHeight),
        .density = iceDensity,
        .maxHp = CalculateHp(iceBaseHP, rectSWidth, rectXHeight),
        .normalTextures = {{"IceRectS", 0.f}},
        .damageTextures = {{"IceRectSDamaged1",0.f}, {"IceRectSDamaged2", 0.f}, {"IceRectSDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };

    ObjectDefaults iceRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectMWidth, rectXHeight),
        .density = iceDensity,
        .maxHp = CalculateHp(iceBaseHP, rectMWidth, rectXHeight),
        .normalTextures = {{"IceRectM", 0.f}},
        .damageTextures = {{"IceRectMDamaged1",0.f}, {"IceRectMDamaged2", 0.f}, {"IceRectMDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };

    ObjectDefaults iceRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectLWidth, rectXHeight),
        .density = iceDensity,
        .maxHp = CalculateHp(iceBaseHP, rectLWidth, rectXHeight),
        .normalTextures = {{"IceRectL", 0.f}},
        .damageTextures = {{"IceRectLDamaged1",0.f}, {"IceRectLDamaged2", 0.f}, {"IceRectLDamaged3", 0.f}},
        .destroySoundNames = iceDestroySoundNames,
        .collisionSoundNames = iceCollisionSoundNames,
        .damageSoundNames = iceDamageSoundNames
    };

    // WOOD
    const float woodDensity = 1.2f;
    const float woodBaseHP = 150.0f;

    std::vector<std::string> woodCollisionSoundNames = { "wood collision a1", "wood collision a2", "wood collision a3",
            "wood collision a4", "wood collision a5" };
    std::vector<std::string> woodDamageSoundNames = { "wood damage a1", "wood damage a2", "wood damage a3" };
    std::vector<std::string> woodDestroySoundNames = { "wood destroyed a1", "wood destroyed a2", "wood destroyed a3" };
    std::vector<std::string> woodOtherSoundNames = { "wood rolling" };

    ObjectDefaults woodCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(circleSRadius),
        .density = woodDensity,
        .maxHp = CalculateHp(woodBaseHP, circleSRadius),
        .normalTextures = {{"WoodCircleS", 0.f}},
        .damageTextures = {{"WoodCircleSDamaged1",0.f}, {"WoodCircleSDamaged2", 0.f}, {"WoodCircleSDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    ObjectDefaults woodCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(circleMRadius),
        .density = woodDensity,
        .maxHp = CalculateHp(woodBaseHP, circleMRadius),
        .normalTextures = {{"WoodCircleM", 0.f}},
        .damageTextures = {{"WoodCircleMDamaged1",0.f}, {"WoodCircleMDamaged2", 0.f}, {"WoodCircleMDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    ObjectDefaults woodSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(squareSize, squareSize),
        .density = woodDensity,
        .maxHp = CalculateHp(woodBaseHP, squareSize, squareSize),
        .normalTextures = {{"WoodSquare", 0.f}},
        .damageTextures = {{"WoodSquareDamaged1",0.f}, {"WoodSquareDamaged2", 0.f}, {"WoodSquareDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    ObjectDefaults woodTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(triangleSize, triangleSize, true),
        .density = woodDensity,
        .maxHp = CalculateHpTriangle(woodBaseHP, triangleSize, triangleSize),
        .normalTextures = {{"WoodTriangleLeft", 0.f}},
        .damageTextures = {{"WoodTriangleLeftDamaged1",0.f}, {"WoodTriangleLeftDamaged2", 0.f}, {"WoodTriangleLeftDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    ObjectDefaults woodTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(triangleSize, triangleSize, false),
        .density = woodDensity,
        .maxHp = CalculateHpTriangle(woodBaseHP, triangleSize, triangleSize),
        .normalTextures = {{"WoodTriangleRight", 0.f}},
        .damageTextures = {{"WoodTriangleRightDamaged1",0.f}, {"WoodTriangleRightDamaged2", 0.f}, {"WoodTriangleRightDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    ObjectDefaults woodRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectWidth, rectHeight),
        .density = woodDensity,
        .maxHp = CalculateHp(woodBaseHP, rectWidth, rectHeight),
        .normalTextures = {{"WoodRect", 0.f}},
        .damageTextures = {{"WoodRectDamaged1",0.f}, {"WoodRectDamaged2", 0.f}, {"WoodRectDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    ObjectDefaults woodRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectSWidth, rectXHeight),
        .density = woodDensity,
        .maxHp = CalculateHp(woodBaseHP, rectSWidth, rectXHeight),
        .normalTextures = {{"WoodRectS", 0.f}},
        .damageTextures = {{"WoodRectSDamaged1",0.f}, {"WoodRectSDamaged2", 0.f}, {"WoodRectSDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    ObjectDefaults woodRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectMWidth, rectXHeight),
        .density = woodDensity,
        .maxHp = CalculateHp(woodBaseHP, rectMWidth, rectXHeight),
        .normalTextures = {{"WoodRectM", 0.f}},
        .damageTextures = {{"WoodRectMDamaged1",0.f}, {"WoodRectMDamaged2", 0.f}, {"WoodRectMDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    ObjectDefaults woodRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectLWidth, rectXHeight),
        .density = woodDensity,
        .maxHp = CalculateHp(woodBaseHP, rectLWidth, rectXHeight),
        .normalTextures = {{"WoodRectL", 0.f}},
        .damageTextures = {{"WoodRectLDamaged1",0.f}, {"WoodRectLDamaged2", 0.f}, {"WoodRectLDamaged3", 0.f}},
        .destroySoundNames = woodDestroySoundNames,
        .collisionSoundNames = woodCollisionSoundNames,
        .damageSoundNames = woodDamageSoundNames,
        .otherSoundNames = woodOtherSoundNames
    };

    // STONE
    const float stoneDensity = 2.6f;
    const float stoneBaseHP = 350.0f;

    std::vector<std::string> stoneCollisionSoundNames = { "rock collision a1", "rock collision a2", "rock collision a3", "rock collision a4", "rock collision a5" };
    std::vector<std::string> stoneDamageSoundNames = { "rock damage a1", "rock damage a2", "rock damage a3" };
    std::vector<std::string> stoneDestroySoundNames = { "rock destroyed a1", "rock destroyed a2", "rock destroyed a3" };
    std::vector<std::string> stoneOtherSoundNames = { "rock rolling" };    

    ObjectDefaults stoneCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(circleSRadius),
        .density = stoneDensity,
        .maxHp = CalculateHp(stoneBaseHP, circleSRadius),
        .normalTextures = {{"StoneCircleS", 0.f}},
        .damageTextures = {{"StoneCircleSDamaged1",0.f}, {"StoneCircleSDamaged2", 0.f}, {"StoneCircleSDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };

    ObjectDefaults stoneCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(circleMRadius),
        .density = stoneDensity,
        .maxHp = CalculateHp(stoneBaseHP, circleMRadius),
        .normalTextures = {{"StoneCircleM", 0.f}},
        .damageTextures = {{"StoneCircleMDamaged1",0.f}, {"StoneCircleMDamaged2", 0.f}, {"StoneCircleMDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };

    ObjectDefaults stoneSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(squareSize, squareSize),
        .density = stoneDensity,
        .maxHp = CalculateHp(stoneBaseHP, squareSize, squareSize),
        .normalTextures = {{"StoneSquare", 0.f}},
        .damageTextures = {{"StoneSquareDamaged1",0.f}, {"StoneSquareDamaged2", 0.f}, {"StoneSquareDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };

    ObjectDefaults stoneTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(triangleSize, triangleSize, true),
        .density = stoneDensity,
        .maxHp = CalculateHpTriangle(stoneBaseHP, triangleSize, triangleSize),
        .normalTextures = {{"StoneTriangleLeft", 0.f}},
        .damageTextures = {{"StoneTriangleLeftDamaged1", 0.f}, {"StoneTriangleLeftDamaged2", 0.f}, {"StoneTriangleLeftDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };

    ObjectDefaults stoneTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShapeTriangle(triangleSize, triangleSize, false),
        .density = stoneDensity,
        .maxHp = CalculateHpTriangle(stoneBaseHP, triangleSize, triangleSize),
        .normalTextures = {{"StoneTriangleRight", 0.f}},
        .damageTextures = {{"StoneTriangleRightDamaged1", 0.f}, {"StoneTriangleRightDamaged2", 0.f}, {"StoneTriangleRightDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };

    ObjectDefaults stoneRect = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectWidth, rectHeight),
        .density = stoneDensity,
        .maxHp = CalculateHp(stoneBaseHP, rectWidth, rectHeight),
        .normalTextures = {{"StoneRect", 0.f}},
        .damageTextures = {{"StoneRectDamaged1", 0.f}, {"StoneRectDamaged2", 0.f}, {"StoneRectDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };

    ObjectDefaults stoneRectS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectSWidth, rectXHeight),
        .density = stoneDensity,
        .maxHp = CalculateHp(stoneBaseHP, rectSWidth, rectXHeight),
        .normalTextures = {{"StoneRectS", 0.f}},
        .damageTextures = {{"StoneRectSDamaged1", 0.f}, {"StoneRectSDamaged2", 0.f}, {"StoneRectSDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };
    
    ObjectDefaults stoneRectM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectMWidth, rectXHeight),
        .density = stoneDensity,
        .maxHp = CalculateHp(stoneBaseHP, rectMWidth, rectXHeight),
        .normalTextures = {{"StoneRectM", 0.f}},
        .damageTextures = {{"StoneRectMDamaged1", 0.f}, {"StoneRectMDamaged2", 0.f}, {"StoneRectMDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };
    
    ObjectDefaults stoneRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(rectLWidth, rectXHeight),
        .density = stoneDensity,
        .maxHp = CalculateHp(stoneBaseHP, rectLWidth, rectXHeight),
        .normalTextures = {{"StoneRectL", 0.f}},
        .damageTextures = {{"StoneRectLDamaged1", 0.f}, {"StoneRectLDamaged2", 0.f}, {"StoneRectLDamaged3", 0.f}},
        .destroySoundNames = stoneDestroySoundNames,
        .collisionSoundNames = stoneCollisionSoundNames,
        .damageSoundNames = stoneDamageSoundNames,
        .otherSoundNames = stoneOtherSoundNames
    };

    // FIXED
    ObjectDefaults fixedCircleS = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(circleSRadius),
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneCircleS", 0.f}}
    };

    ObjectDefaults fixedCircleM = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(circleMRadius),
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneCircleM", 0.f}}
    };

    ObjectDefaults fixedSquare = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(squareSize, squareSize),
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneSquare", 0.f}}
    };

    ObjectDefaults fixedTriangleLeft = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShapeTriangle(triangleSize, triangleSize, true),
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneTriangleLeft", 0.f}}
    };

    ObjectDefaults fixedTriangleRight = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShapeTriangle(triangleSize, triangleSize, false),
        .maxHp = FLT_MAX,
        .normalTextures = {{"StoneTriangleRight", 0.f}}
    };
    
    ObjectDefaults fixedRectL = {
        .bodyDef = GetBodyDef(b2BodyType::b2_staticBody),
        .shape = CreateShape(rectLWidth, rectXHeight),
        .maxHp = FLT_MAX,
        .normalTextures = {{"ground1", 0.f}}
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
