#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "object_defs.hpp"

#ifndef OBJECT_BIRD_HPP
#define OBJECT_BIRD_HPP

/**
 * @brief Abstract physics bird class.
 */
class Bird : public Object
{
public:
    Bird(){}
    Bird(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults, float rot=0.0f) :
        Object(world, x, y, defaults, rot) {
            disableOnDestroy = false;
        }

    /**
     * @brief Bird does a special attack
     */
    virtual void Attack() = 0;

    /**
     * @brief Is worldPos on top of bird?
     * @param worldPos Position in game world
     * @return true if on top
     */
    bool contains(const b2Vec2& worldPos) const {
        if (CurrentHP <= 0) return false;
        b2Fixture* fixture = body->GetFixtureList();
        return fixture->TestPoint(worldPos);        
    }

    bool getCanAttack() { return canAttack; }


    // virtual bool TakeDamage(float dmg) override {
    //     bool isDead = CurrentHP <= 0;
    //     CurrentHP = std::max(0.0f, CurrentHP - dmg);
        
    //     if (CurrentHP <= 0) {
    //         playSound("bird destroyed");
    //         if (!isDead) Destroy(3.0f);
    //     } else if (dmg > 10.0f) {
    //         playSound(rand() % 4);
    //     }

    //     if (!isDamaged) {isDamaged = true;}

    //     return CurrentHP <= 0;
    // }

    virtual bool TakeDamage(float dmg) override {
        CurrentHP = std::max(0.0f, CurrentHP - dmg);

        if (!isDamaged) {
            isDamaged = true;
            playSound("bird destroyed");
            // Destroy(3.0f);
        }

        return CurrentHP <= 0;
    }

    virtual bool TakeDamage(float dmg) override {
        // Textures?
        canAttack = false;
        bool isDead = CurrentHP <= 0;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);
        
        if (CurrentHP <= 0) {
            if (!isDead && canAttack) Destroy(2.0f);
        } else if (dmg > 30.f) {
            playSound(soundType::damage);
        } else if (dmg > 1.f) {
            playSound(soundType::collision);
        }

        if (!isDamaged) {isDamaged = true;}

        return CurrentHP <= 0;
    }


    bool isMoving() const {
        return body->GetLinearVelocity().LengthSquared() > 0;
    }

    void useBird() {used = true;}
    bool isUsed() {return used;}

protected:
    bool canAttack = true;
    bool used = false;
};


#endif
