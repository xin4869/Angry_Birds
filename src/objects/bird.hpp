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
    Bird(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults, float rot=0.f, bool attackFlag=false) :
        Object(world, x, y, defaults, rot), attackOnCollision(attackFlag) {
            disableOnDestroy = false;
            hasDestroyTexture = true;
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

    /**
     * @brief Reduce attack timer, attack when timer reaches 0
     * @param deltaTime Time since last frame
     */
    void scheduleAttack(float deltaTime) {
        attackTimer += deltaTime;
        if (attackTimer > 2.f) {
            Attack();
        }
    }

    virtual void checkDamage() override {
        if (!isDamaged) {
            animationTimer = 0;
            isDamaged = true;
        }
    }

    bool isMoving() const {
        return body->GetLinearVelocity().LengthSquared() > 1.f;
    }
    
    bool getCanAttack() { return canAttack; }
    bool canAttackOnCollision() {return attackOnCollision;}
    bool getIsDamaged(){ return isDamaged;}
    void useBird() {used = true;}
    bool isUsed() {return used;}

protected:
    bool canAttack = true;
    bool used = false;
    bool attackOnCollision;
    float attackTimer = 0.f;
};


#endif
