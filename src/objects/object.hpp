#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "object_defs.hpp"
#include "../visual/texture_manager.hpp"
#include "../sound_manager.hpp"

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
        std::vector<std::string> soundNames,
        float hp
    ): textures(textureDefs), MaxHP(hp), CurrentHP(hp) {
        if (textureDefs.size() == 0) {
            std::cout << "No textures for object" << std::endl;
        }

        for (auto i: soundNames)
        {
            sounds.emplace(std::make_pair(i, sf::Sound()));
            sounds[i].setBuffer(*SoundManager::getSound(i));
        }

        sprite = ObjectDefs::CreateSprite(spriteWidth, spriteHeight, TextureManager::getTexture(textures[0]));      
        bodyDef->position.Set(x, y);
        body = world->CreateBody(bodyDef);
        body->CreateFixture(shape, density);
        body->SetTransform(b2Vec2(x,y), 0);
    }

    Object(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults) :
        Object(world, &defaults->bodyDef, defaults->shape.get(), defaults->density,
            x, y, defaults->spriteWidth, defaults->spriteHeight, defaults->textureNames,
            defaults->soundNames, defaults->maxHp) {}

   // TO DO: make this pure virtual? birds should die after one hit, 
   //          but texture can be updated according to the damage taken
    virtual void TakeDamage(float dmg){
        CurrentHP -= dmg;
        if (CurrentHP <= 0) {
            CurrentHP = 0;
            /// TO DO: delete object after some time??
        }
        updateTexture();
    } 

    void Destroy(){}; /// TO DO: delete object

    virtual void updateTexture(){
        if (textures.size() > 1) {
            size_t idx = static_cast<size_t>((textures.size() - 1) * (1 - CurrentHP/MaxHP));
            idx = std::min(idx, textures.size());
            sprite.setTexture(TextureManager::getTexture(textures[idx]));
        }
    }

    bool playSound(const std::string& name)
    {
        sounds[name].play();
    }

protected :
    b2Body* body;
    sf::Sprite sprite;
    std::vector<std::string> textures;
    std::unordered_map<std::string, sf::Sound> sounds;  // <name, sound>
    float MaxHP;
    float CurrentHP;
};


#endif
