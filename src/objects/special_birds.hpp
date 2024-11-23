#include "bird.hpp"
#include "object_defs.hpp"
#include <iostream>

#ifndef OBJECT_SPECIAL_BIRD_HPP
#define OBJECT_SPECIAL_BIRD_HPP

namespace ObjectDefs
{
    ObjectDefaults* getBirdDefaults(const std::string& birdName) {
        if (birdName == "normalBird") return &normalBirdDefaults;
        if (birdName == "speedBird") return &speedBirdDefaults;
        if (birdName == "explodeBird") return &explodeBirdDefaults;
        return nullptr;
    }

    ObjectDefaults normalBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 1.0f,
        .spriteHeight = pixel_per_meter * 1.0f,
        .normalTextures = { "NormalBird1", "NormalBird2"},
        .damageTextures = { "NormalBirdDead"}
    };

    ObjectDefaults speedBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 1.0f,
        .spriteHeight = pixel_per_meter * 1.0f,
        .normalTextures = { "SpeedBird1", "SpeedBird2", "SpeedBird3", "SpeedBird4"},
        .damageTextures = { "SpeedBirdDead"}
    };

    ObjectDefaults explodeBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 1.0f,
        .spriteHeight = pixel_per_meter * 1.0f,
        .normalTextures = { "ExplodeBird1", "ExplodeBird2", "ExplodeBird3", "ExplodeBird4"},
        .damageTextures = { "ExplodeBirdDead"}
    };
}
/**
 * @brief Physics bird with a special attack (not this one)
 * 
 */
class NormalBird : public Bird
{
public:
    /**
     * @brief Construct a new Normal Bird. Uses default values.
     */
    NormalBird(b2World* world, float x, float y) :
        Bird(world, x, y, &ObjectDefs::normalBirdDefaults) {}

    void Attack()
    {
        std::cout << "Bird Attacked" << std::endl;
    }
};


#endif
