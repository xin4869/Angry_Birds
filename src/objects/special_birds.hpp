#include "bird.hpp"
#include "object_defs.hpp"
#include <iostream>

#ifndef OBJECT_SPECIAL_BIRD_HPP
#define OBJECT_SPECIAL_BIRD_HPP

namespace ObjectDefs
{
    ObjectDefaults normalBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 1.0f,
        .spriteHeight = pixel_per_meter * 1.0f,
        .textureNames = { "NormalBird1", "NormalBird2", "NormalBird3", "NormalBird4", "NormalBird5", "NormalBird6", "NormalBird7" },
        .soundNames = { "bird 01 collision a1", "bird 01 collision a2", "bird 01 collision a3", "bird 01 collision a4", "bird 01 flying", "bird 01 select", "bird destroyed" }
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
