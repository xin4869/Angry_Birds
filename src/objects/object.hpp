#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include "object_defs.hpp"
#include "../visual/texture_manager.hpp"
#include "../sound_manager.hpp"

#ifndef OBJECT_HPP
#define OBJECT_HPP

/**
 * @brief Represents a basic physics object.
 */
class Object
{
public:
    Object(){}
    virtual ~Object(){
        body->GetWorld()->DestroyBody(body);
    }

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
        std::vector<std::string> soundNames,
        float hp
    ): normalTextures(textureDefs), damageTextures(damageTextureDefs), 
        MaxHP(hp), CurrentHP(hp) {

        if (normalTextures.size() == 0) {
            std::cout << "No textures for object" << std::endl;
        }

        for (auto i: soundNames)
        {
            const sf::SoundBuffer* sound = SoundManager::getSound(i);
            if (!sound) continue;
            sounds.emplace(std::make_pair(i, sf::Sound()));
            sounds[i].setBuffer(*sound);
        }
        const sf::Texture& txt = TextureManager::getTexture(normalTextures[0]);
        sprite = ObjectDefs::CreateSprite(spriteWidth, spriteHeight, txt);
        bodyDef->position.Set(x, y);
        body = world->CreateBody(bodyDef);
        body->CreateFixture(shape, density);
        body->SetTransform(b2Vec2(x,y), 0);
        body->GetUserData().pointer = (uintptr_t)this;
    }

    Object(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults) :
        Object(world, &defaults->bodyDef, defaults->shape.get(), defaults->density,
            x, y, defaults->spriteWidth, defaults->spriteHeight, defaults->normalTextures,
            defaults->damageTextures, defaults->soundNames, defaults->maxHp) {}
    
   /**
    * @brief Overridden in subclasses. Set functionality there.
    * @param dmg damage taken
    * @return true if killed
    */
    virtual bool TakeDamage(float dmg){
        CurrentHP = std::max(0.0f, CurrentHP - dmg);

        if (!isDamaged) {
            isDamaged = true;
            if (isAnimated) {
                currentTextureIdx = 0;
            }
        }
        return CurrentHP <= 0;
    } 

    /**
     * @brief Delete object in timer_s seconds (deleted by Level).
     * @brief Objects need to be deleted between steps
     * @brief and sounds take time to finish.
     * @param timer_s time to deletion
     */
    void Destroy(float timer_s=0.0f){
        destroyList.push_back(std::make_pair(timer_s, this));
    }

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

    bool playSound(const std::string& name)
    {
        if (sounds.find(name) == sounds.end()) return false;
        sounds[name].play();
        return true;
    }

    bool playSound(size_t index) {
        if (index >= sounds.size()) return false;
        auto start = sounds.begin();
        for (size_t i = 0; i < index; i++) start++;
        (*start).second.play();
        return true;
    }

    b2Body* getBody() { return body; }
    float getScore() { return score; }
    float getMaxHP() { return MaxHP; }
    float getHP() { return CurrentHP; }
    constexpr const static float speedDamageMultiplier = 10.0f;  // tune this value
    static std::list< std::pair< float, Object* > > destroyList;  // <timer, object>

protected :
    b2Body* body;
    sf::Sprite sprite;
    std::vector<std::string> normalTextures;
    std::vector<std::string> damageTextures;

    std::map<std::string, sf::Sound> sounds;  // <name, sound>
    float MaxHP;
    float CurrentHP;
    float score = 0;

    bool isAnimated = true;
    bool isDamaged = false;
    size_t currentTextureIdx = 0;
    float animationTimer = 0.0f;
};

std::list< std::pair< float, Object* > > Object::destroyList;

class ObjectCollisions : public b2ContactListener
{
    /**
     * @brief Handles collisions between Objects, adds score.
     * @brief Damage increases linearly with difference in velocity.
     * @param contact supplied by box2d
     */
    void BeginContact(b2Contact* contact) {
        b2Body* body1 = contact->GetFixtureA()->GetBody();
        b2Body* body2 = contact->GetFixtureB()->GetBody();

        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);
        b2Vec2 contactPoint = worldManifold.points[0];

        // Guess this works?
        float deltaVel = (body1->GetLinearVelocityFromWorldPoint(contactPoint) -
                body2->GetLinearVelocityFromWorldPoint(contactPoint)).Length();
        
        void* bodyData1 = (void*)body1->GetUserData().pointer;
        void* bodyData2 = (void*)body2->GetUserData().pointer;
        
        // consider mass / density too?
        float dmg = deltaVel * Object::speedDamageMultiplier;
        bool killed;
        Object* object;

        if (bodyData1) {
            object = static_cast<Object*>(bodyData1);
            killed = object->TakeDamage(dmg);
            if (killed) scoreToAdd += object->getScore();
        }
        if (bodyData2) {
            object = static_cast<Object*>(bodyData2);
            killed = object->TakeDamage(dmg);
            if (killed) scoreToAdd += object->getScore();
        }
    }

public:
    /**
     * @brief Gives score from collisions, resets.
     * @brief Does not need to know about other score sources.
     * @return score
     */
    float transferScore() {
        float score = scoreToAdd;
        scoreToAdd = 0;
        return score;
    }

private:
    float scoreToAdd = 0;
};

/**
 * @brief Raycasting for explosions :D.
 * @brief Hits first target in the way
 */
class RayCastHitFirst : public b2RayCastCallback
{
public:
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
        hitLatest = fixture;
        hitPoint = point;
        return fraction;
    }

    b2Fixture* hitLatest = nullptr;
    b2Vec2 hitPoint;
};

#endif
