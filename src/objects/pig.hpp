#include "object.hpp"
#include "object_defs.hpp"

#ifndef OBJECT_PIG_HPP
#define OBJECT_PIG_HPP

namespace ObjectDefs
{
    ObjectDefaults normalPigDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 1.0f,
        .spriteHeight = pixel_per_meter * 1.0f,
        .normalTextures = { "Pig1", "Pig2", "Pig3"},
        .damageTextures = { "PigDamage1", "PigDamage2"}
    };

    ObjectDefaults ironPigDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 300.0f,
        .spriteWidth = pixel_per_meter * 1.0f,
        .spriteHeight = pixel_per_meter * 1.0f,
        .normalTextures = { "IronPig1", "IronPig2", "IronPig3"},
        .damageTextures = { "IronPigDamage1", "IronPigDamage2"}
    };
}

/**
 * @brief Pig class.
 * @brief No subclasses since pigs are functionally the same.
 * @brief Instead we have static variant getters.
 * 
 */
class Pig : public Object
{
public:
    /**
     * @brief Construct a new Pig object
     * 
     * @param defaults default values
     */
    Pig(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults):
        Object(world, x, y, defaults) {}
};

#endif
