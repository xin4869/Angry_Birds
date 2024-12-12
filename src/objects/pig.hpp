#include "object.hpp"
#include "object_defs.hpp"

#ifndef OBJECT_PIG_HPP
#define OBJECT_PIG_HPP

namespace ObjectDefs
{
    std::vector<std::string> pigSoundNames = { "piglette damage a4", "piglette damage a7", "piglette destroyed" };
    const float pigRadius = 1.0f;
    const float pigDensity = 1.0f;

    ObjectDefaults normalPigDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(pigRadius),
        .density = pigDensity,
        .maxHp = 100.0f,
        .normalTextures = { {"Pig1", 3.f}, {"Pig2", 0.4f}, {"Pig3", 1.f}},
        .damageTextures = { {"PigDamage1", 3.f}, {"PigDamage2", 0.4f}, {"PigDamage3", 3.f}, {"PigDamage4", 0.4f}},
        .soundNames = pigSoundNames
    };

    ObjectDefaults ironPigDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(pigRadius),
        .density = pigDensity,
        .maxHp = 300.0f,
        .normalTextures = { {"IronPig1", 3.f}, {"IronPig2", 0.4f}, {"IronPig3", 2.f}},
        .damageTextures = { {"IronPigDamage1", 3.f}, {"IronPigDamage2", 0.4f}, {"IronPigDamage3", 3.f}, {"IronPigDamage4", 0.4f}},
        .soundNames = pigSoundNames
    };

    ObjectDefaults* getPigDefaults(const std::string& pigName) {
        if (pigName == "normalpig") return &normalPigDefaults;
        if (pigName == "ironpig") return &ironPigDefaults;
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
    Pig(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults, float rot=0.0f):
        Object(world, x, y, defaults, rot) { score = 500.0f; }


    virtual bool TakeDamage(float dmg) override {
        // bool isDead = CurrentHP <= 0;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
        float hp_percent = CurrentHP / MaxHP;
        if (!isDamaged && hp_percent<= 0.6f) {
            isDamaged = true;
            currentTextureIdx = 0;
        }
       
        if (CurrentHP <= 0) {
            playSound("piglette destroyed");
            // if (!isDead) Destroy(3.0f);
        } else if (dmg > 10.0f) {
            playSound(rand() % 2);
        }

        return CurrentHP <= 0;
    }

    virtual void updateTexture(float deltaTime) override {
        animationTimer += deltaTime;
        float hp_percent = CurrentHP / MaxHP;
        if (hp_percent > 0.6f) {
            if (animationTimer > normalTextures[currentTextureIdx].second) {
                animationTimer = 0;
                column += 1; 
                if (column > texture_order[row].size() - 1) {
                    column = 0;
                    row = rand() % texture_order.size();
                }
                currentTextureIdx = texture_order[row][column];
                sprite.setTexture(TextureManager::getTexture(normalTextures[currentTextureIdx].first));
            }
        } else if (0.3f < hp_percent && hp_percent <= 0.6f) {
            // sprite.setTexture(TextureManager::getTexture(damageTextures[currentTextureIdx].first));
            if (animationTimer > damageTextures[currentTextureIdx].second) {
                animationTimer = 0; 
                currentTextureIdx = (currentTextureIdx + 1) % 2;
            }
            sprite.setTexture(TextureManager::getTexture(damageTextures[currentTextureIdx].first));
        } else {
            if (currentTextureIdx < 2 || currentTextureIdx > damageTextures.size()) {
                currentTextureIdx = damage_start_idx;
            }
            if (animationTimer > damageTextures[currentTextureIdx].second) {
                animationTimer = 0;
                currentTextureIdx = currentTextureIdx + 1;
                if (currentTextureIdx > damageTextures.size() - 1) {
                    currentTextureIdx = damage_start_idx;
                }
            }
            sprite.setTexture(TextureManager::getTexture(damageTextures[currentTextureIdx].first)); 
        }
    }

private:
    std::vector<std::vector<size_t>> texture_order = {{0,1}, {0,2}};
    size_t row = 0;
    size_t column = 0;
    size_t damage_start_idx = 2;
};

#endif
