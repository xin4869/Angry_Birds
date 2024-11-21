#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "object_defs.hpp"
#include "../visual/texture_manager.hpp"

#ifndef OBJECT_HPP
#define OBJECT_HPP

/**
 * @brief Represents a basic physics object. Might make this abstract later.
 * 
 */

class Object
{
public:
    Object(){};
    ~Object(){};

    Object(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        float spriteWidth,
        float spriteHeight,
        std::vector<std::string> textureDefs, 
        std::vector<std::string> damageTextureDefs,
        float hp
    ): normalTextures(textureDefs), damageTextures(damageTextureDefs), 
        MaxHP(hp), CurrentHP(hp) {

        if (normalTextures.size() == 0) {
            std::cout << "No textures for object" << std::endl;
        }
        sprite = ObjectDefs::CreateSprite(spriteWidth, spriteHeight, TextureManager::getTexture(normalTextures[0]));      
        bodyDef->position.Set(x, y);
        body = world->CreateBody(bodyDef);
        body->CreateFixture(shape, density);
        body->SetTransform(b2Vec2(x,y), 0);
    }

    Object(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults) :
        Object(world, &defaults->bodyDef, defaults->shape.get(), defaults->density, x, y,
            defaults->spriteWidth, defaults->spriteHeight, defaults->normalTextures,
            defaults->damageTextures, defaults->maxHp) {}

   // TODO: make this pure virtual? birds should die after one hit, 
   //          but texture can be updated according to the damage taken
    virtual void TakeDamage(float dmg){
        CurrentHP = std::max(0.0f, CurrentHP - dmg);

        if (!isDamaged) {
            isDamaged = true;
            if (isAnimated) {
                currentTextureIdx = 0;
            }
        }
    } 

    void Destroy(){}; /// TODO: delete object after some time?

    virtual void updateTexture(float deltaTime){
        const auto& textures = isDamaged? damageTextures:normalTextures;
        if (isAnimated) {
            animationTimer += deltaTime;
            if (animationTimer >= 0.1f) {
                animationTimer = 0.0f;               
                currentTextureIdx = (currentTextureIdx + 1) % textures.size();
                sprite.setTexture(TextureManager::getTexture(textures[currentTextureIdx]));
            }
        } else {
            if (!textures.empty()) {        
                size_t idx = isDamaged? 
                static_cast<size_t>((textures.size() - 1) * (1 - CurrentHP/MaxHP)) : 0;              
                idx = std::min(idx, textures.size() - 1);
                sprite.setTexture(TextureManager::getTexture(textures[idx]));
            } 
        }       
    }

protected :
    b2Body* body;
    sf::Sprite sprite;
    std::vector<std::string> normalTextures;
    std::vector<std::string> damageTextures;

    float MaxHP;
    float CurrentHP;

    bool isAnimated = true;
    bool isDamaged = false;
    size_t currentTextureIdx = 0;
    float animationTimer = 0.0f;
};


#endif
