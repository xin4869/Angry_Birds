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
        Object(world, x, y, defaults, rot) {}

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

protected:
    bool canAttack = true;
};


#endif
