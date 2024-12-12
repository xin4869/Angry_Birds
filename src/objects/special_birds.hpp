#include <iostream>
#include "bird.hpp"
#include "object_defs.hpp"

#ifndef OBJECT_SPECIAL_BIRD_HPP
#define OBJECT_SPECIAL_BIRD_HPP

namespace ObjectDefs
{
    const float birdRadius = 1.0f;
    const float birdDensity = 1.0f;
    const float birdMaxHp = 100.0f;

    ObjectDefaults normalBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(birdRadius),
        .density = birdDensity,
        .maxHp = birdMaxHp,
        .normalTextures = {{"NormalBird1", 2.f}, {"NormalBird2", 0.1f}},
        .damageTextures = {{"NormalBirdDead", 0.f}},
        .soundNames = { "bird 01 collision a1", "bird 01 collision a2", "bird 01 collision a3", "bird 01 collision a4",
                "bird 01 flying", "bird 01 select", "bird destroyed" }
    };

    ObjectDefaults speedBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(birdRadius),
        .density = birdDensity,
        .maxHp = birdMaxHp,
        .normalTextures = {{"SpeedBird1", 2.f}, {"SpeedBird2", 0.1f}, {"SpeedBird3", 0.8f}, {"SpeedBird4", 0.8f}},
        .damageTextures = {{"SpeedBirdDead", 0.f}},
        .soundNames = { "bird 03 collision a1", "bird 03 collision a2", "bird 03 collision a3", "bird 03 collision a4",
                "bird 03 flying", "bird 03 select", "bird destroyed", "special boost" }
    };

    ObjectDefaults explodeBirdDefaults = {
        .bodyDef = GetBodyDef(b2BodyType::b2_dynamicBody),
        .shape = CreateShape(birdRadius),
        .density = birdDensity,
        .maxHp = birdMaxHp,
        .normalTextures = {{"ExplodeBird1", 2.f}, {"ExplodeBird2", 0.1f}, {"ExplodeBird3", 0.1f}, {"ExplodeBird4", 0.1f}, {"ExplodeBird5", std::numeric_limits<float>::max()}},
        .damageTextures = {{"ExplodeBirdDead", 0.f}},
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
class NormalBird : public Bird {
public:
    NormalBird(){}
    NormalBird(b2World* world, float x, float y, float rot=0.0f) :
        Bird(world, x, y, &ObjectDefs::normalBirdDefaults, rot) {}


    void Attack() override {
        if (!canAttack) return;
        canAttack = false;
        playSound("bird 01 select");
    }

    /**
     * @brief Take damage, play sounds, destroy if killed
     * @param dmg damage
     */

    virtual void updateTexture(float deltaTime) override {
        if (isDamaged) {
            sprite.setTexture(TextureManager::getTexture(damageTextures[0].first));
        } else {     
            animationTimer += deltaTime;     
            if (animationTimer >= normalTextures[currentTextureIdx].second) {
                animationTimer = 0.0f;               
                currentTextureIdx = (currentTextureIdx + 1) % normalTextures.size();
                sprite.setTexture(TextureManager::getTexture(normalTextures[currentTextureIdx].first));
            }
        }
    }

};

class SpeedBird : public Bird
{
public:
    SpeedBird(b2World* world, float x, float y, float rot=0.0f) :
        Bird(world, x, y, &ObjectDefs::speedBirdDefaults, rot) {}

    void Attack() override {
        if (!canAttack) return;
        canAttack = false;
        b2Vec2 vel = body->GetLinearVelocity();
        float length = vel.Length();
        if (length > 0) vel *= (length + abilitySpeedGain) / length;  // add constant velocity
        body->SetLinearVelocity(vel);
        playSound("special boost");
    }


    virtual void updateTexture(float deltaTime) override {
        if (isDamaged) {
            sprite.setTexture(TextureManager::getTexture(damageTextures[0].first));
        } else {
            animationTimer += deltaTime;
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
        }
    }

protected:
    const float abilitySpeedGain = 20.0f;  // tune this value
    std::vector<std::vector<size_t>> texture_order = {{0,1}, {0,2,3,2}};
    size_t row = 0;
    size_t column = 0;

};

class ExplodeBird : public Bird
{
public:
    ExplodeBird(b2World* world, float x, float y, float rot=0.0f) :
        Bird(world, x, y, &ObjectDefs::explodeBirdDefaults, rot) {}

    void Attack() override {
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

    virtual bool TakeDamage(float dmg) override {
        // Textures?
        bool isDead = CurrentHP <= 0;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
        
        if (CurrentHP <= 0) {
            playSound("bird destroyed");
            if (!isDead && canAttack) Destroy(2.0f);
        } else if (dmg > 10.0f) {
            playSound(rand() % 4);
        }

        if (!isDamaged) {isDamaged = true;}
        
        return CurrentHP <= 0;
    }


    virtual void updateTexture(float deltaTime) override {
        if (isDamaged) {
            sprite.setTexture(TextureManager::getTexture(damageTextures[0].first));
        } else {
            if (!canAttack) {
                sprite.setTexture(TextureManager::getTexture(normalTextures[4].first));
            } else {
                animationTimer += deltaTime;
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
            }
        }
    }

protected:
    // tune these values
    int blastRays = 32;
    float blastRadius = 5.0f;
    float blastPower = 1000.0f;
    size_t row = 0;
    size_t column = 0;
    std::vector<std::vector<size_t>> texture_order = {{0,1}, {0,2}, {0,3}};
};


#endif
