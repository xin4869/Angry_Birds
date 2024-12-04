#include "object.hpp"
#include "object_defs.hpp"

#ifndef OBJECT_PIG_HPP
#define OBJECT_PIG_HPP

namespace ObjectDefs
{
    std::vector<std::string> pigSoundNames = { "piglette damage a4", "piglette damage a7", "piglette destroyed" };

    ObjectDefaults normalPigDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 1.0f,
        .spriteHeight = pixel_per_meter * 1.0f,
        .normalTextures = { "Pig1", "Pig2", "Pig3"},
        .damageTextures = { "PigDamage1", "PigDamage2"},
        .soundNames = pigSoundNames
    };

    ObjectDefaults ironPigDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 300.0f,
        .spriteWidth = pixel_per_meter * 1.0f,
        .spriteHeight = pixel_per_meter * 1.0f,
        .normalTextures = { "IronPig1", "IronPig2", "IronPig3"},
        .damageTextures = { "IronPigDamage1", "IronPigDamage2"},
        .soundNames = pigSoundNames
    };

    ObjectDefaults* getPigDefaults(const std::string& pigName) {
        if (pigName == "normalPig") return &normalPigDefaults;
        if (pigName == "ironPig") return &ironPigDefaults;
        return nullptr;
    }
}

/**
 * @brief Pig class.
 * @brief No subclasses since pigs are functionally the same.
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
        Object(world, x, y, defaults) { score = 500.0f; }
    
    virtual ~Pig(){}

    virtual bool TakeDamage(float dmg) {
        // TODO: Textures?
        bool isDead = CurrentHP <= 0;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
        
        if (CurrentHP <= 0) {
            playSound("piglette destroyed");
            if (!isDead) Destroy(2.0f);
        } else if (dmg > 10.0f) {
            playSound(rand() % 2);
        }

        return CurrentHP <= 0;
    }
};

#endif
