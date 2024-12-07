#ifndef SLINGSHOT_HPP
#define SLINGSHOT_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "objects/object.hpp"
#include "visual/texture_manager.hpp"
#include "objects/object_defs.hpp"

class Slingshot
{
public:
    // TODO: sfx
    Slingshot(){
        sprite = ObjectDefs::CreateSprite(80, 228, TextureManager::getTexture(textures[0]));
    }
    Slingshot(float x, float y) : pos(x, y) {}

    /**
     * @brief Shoots object towards slingshot. Impulse depends linearly on distance from slingshot
     * @param object launch this
     */
    void launchObject(Object* object) {
        b2Vec2 impulse = pos - object->getBody()->GetPosition();
        if (impulse.LengthSquared() > maxRadius * maxRadius) {
            impulse.Normalize();
            impulse *= maxRadius;
        }
        impulse *= powerMult;
        object->getBody()->ApplyLinearImpulseToCenter(impulse, true);
    }

    /**
     * @brief Drag slingshot and object to x, y. Meant to be called every frame when dragging.
     * 
     * @param object object in slingshot
     * @param x, y drag here (limited by maxRadius)
     */
    void drag(Object* object, float x, float y) {
        // update textures, play audio?
        b2Vec2 offset(x, y);
        offset -= pos;
        if (offset.LengthSquared() > maxRadius * maxRadius) {
            offset.Normalize();
            offset *= maxRadius;
        }
        object->getBody()->SetLinearVelocity(b2Vec2(0, 0));
        object->getBody()->SetTransform(pos + offset, 0);
        sprite.setTexture(TextureManager::getTexture(textures[2]));
    }

    /**
     * @brief Counterpart of drag. Launches the object
     * @param x, y point of release
     */
    void release(Object* object, float x, float y) {
        // update textures, play audio?
        object->getBody()->SetTransform(b2Vec2(x, y), 0);
        launchObject(object);
        sprite.setTexture(TextureManager::getTexture(textures[0]));
    }
    
    float getRadius() { return maxRadius; }
    void setPos(float x, float y) { pos.Set(x, y); }
    void setPos(b2Vec2 newPos) { pos = newPos; }
    b2Vec2& getPos() { return pos; }
    sf::Sprite& getSprite() { return sprite; }

protected:
    b2Vec2 pos;
    float maxRadius = 3.0f;
    float powerMult = 5.0f;  // likely off. modify if necessary
    sf::Sprite sprite;
    std::vector< std::string > textures = { "slingshot1", "slingshot2", "slingshot3" };
};

#endif // SLINGSHOT_HPP
