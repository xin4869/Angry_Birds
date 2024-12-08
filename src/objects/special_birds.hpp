#include <iostream>
#include "bird.hpp"
#include "object_defs.hpp"

#ifndef OBJECT_SPECIAL_BIRD_HPP
#define OBJECT_SPECIAL_BIRD_HPP

namespace ObjectDefs
{
    ObjectDefaults normalBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 2.0f,
        .spriteHeight = pixel_per_meter * 2.0f,
        .normalTextures = { "NormalBird1", "NormalBird2"},
        .damageTextures = { "NormalBirdDead"},
        .soundNames = { "bird 01 collision a1", "bird 01 collision a2", "bird 01 collision a3", "bird 01 collision a4",
                "bird 01 flying", "bird 01 select", "bird destroyed" }
    };

    ObjectDefaults speedBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 2.0f,
        .spriteHeight = pixel_per_meter * 2.0f,
        .normalTextures = { "SpeedBird1", "SpeedBird2", "SpeedBird3", "SpeedBird4"},
        .damageTextures = { "SpeedBirdDead"},
        .soundNames = { "bird 03 collision a1", "bird 03 collision a2", "bird 03 collision a3", "bird 03 collision a4",
                "bird 03 flying", "bird 03 select", "bird destroyed", "special boost" }
    };

    ObjectDefaults explodeBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(1.0f),
        .density = 1.0f,
        .maxHp = 100.0f,
        .spriteWidth = pixel_per_meter * 2.0f,
        .spriteHeight = pixel_per_meter * 2.0f,
        .normalTextures = { "ExplodeBird1", "ExplodeBird2", "ExplodeBird3", "ExplodeBird4"},
        .damageTextures = { "ExplodeBirdDead"},
        .soundNames = { "bird 05 collision a1", "bird 05 collision a2", "bird 05 collision a3", "bird 05 collision a4",
                "bird 05 flying", "bird 05 select", "bird destroyed", "tnt box explodes" }
    };
    
    ObjectDefaults* getBirdDefaults(const std::string& birdName) {
        if (birdName == "normalbird") return &normalBirdDefaults;
        if (birdName == "speedbird") return &speedBirdDefaults;
        if (birdName == "explodebird") return &explodeBirdDefaults;
        return nullptr;
    }

}

/**
 * @brief Physics bird with a special attack (not this one)
 */
class NormalBird : public Bird
{
public:
    NormalBird(){}
    NormalBird(b2World* world, float x, float y, float rot=0.0f) :
        Bird(world, x, y, &ObjectDefs::normalBirdDefaults, rot) {}

    void Attack() {
        if (!canAttack) return;
        canAttack = false;
        playSound("bird 01 select");
    }

    /**
     * @brief Take damage, play sounds, destroy if killed
     * @param dmg damage
     */
    virtual bool TakeDamage(float dmg) {
        // Textures?
        bool isDead = CurrentHP <= 0;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
        
        if (CurrentHP <= 0) {
            playSound("bird destroyed");
            if (!isDead) Destroy(2.0f);
        } else if (dmg > 10.0f) {
            playSound(rand() % 4);
        }

        return CurrentHP <= 0;
    }
};

class SpeedBird : public Bird
{
public:
    SpeedBird(b2World* world, float x, float y, float rot=0.0f) :
        Bird(world, x, y, &ObjectDefs::speedBirdDefaults, rot) {}

    void Attack() {
        if (!canAttack) return;
        canAttack = false;
        b2Vec2 vel = body->GetLinearVelocity();
        float length = vel.Length();
        if (length > 0) vel *= (length + abilitySpeedGain) / length;  // add constant velocity
        body->SetLinearVelocity(vel);
        playSound("special boost");
    }

    virtual bool TakeDamage(float dmg) {
        // Textures?
        bool isDead = CurrentHP <= 0;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
        
        if (CurrentHP <= 0) {
            playSound("bird destroyed");
            if (!isDead) Destroy(2.0f);
        } else if (dmg > 10.0f) {
            playSound(rand() % 4);
        }

        return CurrentHP <= 0;
    }

protected:
    const float abilitySpeedGain = 20.0f;  // tune this value
};

class ExplodeBird : public Bird
{
public:
    ExplodeBird(b2World* world, float x, float y, float rot=0.0f) :
        Bird(world, x, y, &ObjectDefs::explodeBirdDefaults, rot) {}

    void Attack() {
        if (!canAttack) return;
        canAttack = false;
        
        // raycast blast
        RayCastHitFirst raycast;
        for (float i = 0; i < blastRays; i++) {
            float angleRad = i / blastRays * 2.0f * M_PI;
            b2Vec2 dir(cosf(angleRad), sinf(angleRad));
            dir *= blastRadius;
            body->GetWorld()->RayCast(&raycast, body->GetPosition(), body->GetPosition() + dir);
            
            if (raycast.hitLatest) {
                // apply impulse to body
                b2Vec2 impulse = raycast.hitPoint - body->GetPosition();
                float dist = impulse.Normalize();
                impulse *= blastPower / (dist * dist * (float)blastRays);
                raycast.hitLatest->GetBody()->ApplyLinearImpulse(impulse, raycast.hitPoint, true);
                raycast.hitLatest = nullptr;
            }
        }
        playSound("tnt box explodes");
        if (CurrentHP > 0) Destroy(2.0f);
    }

    virtual bool TakeDamage(float dmg) {
        // Textures?
        bool isDead = CurrentHP <= 0;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
        
        if (CurrentHP <= 0) {
            playSound("bird destroyed");
            if (!isDead && canAttack) Destroy(2.0f);
        } else if (dmg > 10.0f) {
            playSound(rand() % 4);
        }

        return CurrentHP <= 0;
    }

protected:
    // tune these values
    int blastRays = 32;
    float blastRadius = 5.0f;
    float blastPower = 1000.0f;
};


#endif
