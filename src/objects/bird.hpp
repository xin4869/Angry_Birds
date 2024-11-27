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
    Bird(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults) :
        Object(world, x, y, defaults) {}

    virtual void Attack() = 0;

protected:
    bool canAttack = true;
};


#endif
