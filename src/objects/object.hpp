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

enum class soundType {
    collision,
    damage,
    destroy,
};

/**
 * @brief Represents a basic physics object.
 */
class Object
{
public:
    Object(){}
    virtual ~Object() {
        body->GetWorld()->DestroyBody(body);
        stopSounds();
    }

    /**
     * @brief Main constructor
     * @param world World to add in
     * @param bodyDef body def
     * @param shape collider
     * @param density 
     * @param x, y world pos
     * @param hp max HP
     * @param textureDefs normal textures
     * @param damageTextureDefs damage textures
     * @param destroySoundNames 
     * @param collisionSoundNames 
     * @param damageSoundNames 
     * @param otherSoundNames 
     * @param rotation in degrees
     */
    Object(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        float hp,
        std::vector<std::pair<std::string, float>> textureDefs, 
        std::vector<std::pair<std::string, float>> damageTextureDefs,
        std::vector<std::string> destroySoundNames,
        std::vector<std::string> collisionSoundNames,
        std::vector<std::string> damageSoundNames,
        std::vector<std::string> otherSoundNames,
        float rotation=0.0f
    ): normalTextures(textureDefs), damageTextures(damageTextureDefs), 
        MaxHP(hp), CurrentHP(hp) {

        if (normalTextures.size() == 0) {
            std::cout << "No textures for object" << std::endl;
        }

        loadSounds(destroySoundNames, collisionSoundNames, damageSoundNames, otherSoundNames);

        if (normalTextures.size() > 0) {
            const sf::Texture& txt = TextureManager::getTexture(normalTextures[0].first);
            sprite = ObjectDefs::CreateSprite(txt);
        }

        bodyDef->position.Set(x, y);
        bodyDef->angle = M_PI / 180.0f * rotation;
        body = world->CreateBody(bodyDef);
        b2Fixture* fix = body->CreateFixture(shape, density);
        fix->SetRestitution(0.3f);

        // tune these
        body->SetAngularDamping(0.8f);
        fix->SetFriction(0.4f);

        body->SetTransform(b2Vec2(x,y), body->GetAngle());
        body->GetUserData().pointer = (uintptr_t)this;
    }

    /**
     * @brief Constructor used by derived classes
     */
    Object(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults, float rotation=0.0f) :
        Object(world, &defaults->bodyDef, defaults->shape.get(), defaults->density,
            x, y, defaults->maxHp, defaults->normalTextures, defaults->damageTextures,
            defaults->destroySoundNames, defaults->collisionSoundNames, defaults->damageSoundNames,
            defaults->otherSoundNames, rotation) {}
    
    /**
     * @brief Loads sounds
     * @param destroySoundNames 
     * @param collisionSoundNames 
     * @param damageSoundNames 
     * @param otherSoundNames 
     */
    void loadSounds(std::vector<std::string> destroySoundNames, std::vector<std::string> collisionSoundNames, 
        std::vector<std::string> damageSoundNames, std::vector<std::string> otherSoundNames) {
        for (auto i: destroySoundNames) {
            const sf::SoundBuffer* sound = SoundManager::getSound(i);
            if (!sound) continue;
            destroySounds.push_back(sf::Sound(*sound));
        }

        for (auto i: collisionSoundNames) {
            const sf::SoundBuffer* sound = SoundManager::getSound(i);
            if (!sound) continue;
            collisionSounds.push_back(sf::Sound(*sound));
        }

        for (auto i: damageSoundNames) {
            const sf::SoundBuffer* sound = SoundManager::getSound(i);
            if (!sound) continue;
            damageSounds.push_back(sf::Sound(*sound));
        }

        for (auto i: otherSoundNames) {
            const sf::SoundBuffer* sound = SoundManager::getSound(i);
            if (!sound) continue;
            otherSoundsMap.emplace(std::make_pair(i, sf::Sound(*sound)));
        }
    }

    /**
     * @brief Stops all sounds
     */
    void stopSounds() {
        for (auto i: destroySounds) {i.stop();}
        for (auto i: collisionSounds) {i.stop();}
        for (auto i: damageSounds) {i.stop();}
        for (auto i: otherSoundsMap) {i.second.stop();}
    }

    /**
     * @brief Plays a sound by name
     * @param name name of the sound
     * @return true if sound was played
     * @return false if sound was not found
     */
    bool playSound(const std::string& name)
    {
        if (otherSoundsMap.find(name) == otherSoundsMap.end()) return false;
        otherSoundsMap[name].play();
        return true;
    }

    bool playSound(soundType sound_type) {
        std::vector<sf::Sound>* target_list = nullptr;
        switch (sound_type) {
            case soundType::destroy:
                target_list = &destroySounds;
                break;
            case soundType::collision:
                target_list = &collisionSounds;
                break;
            case soundType::damage:
                target_list = &damageSounds;
                break;
            
            // default:
            //     return false;
        }
        if (target_list && !target_list->empty()) {
            size_t idx = rand() % target_list->size();
            sf::Sound& sound = (*target_list)[idx];
            if (sound.getStatus() != sf::Sound::Playing) {
                sound.play();
            }
            return true;
        }
        return false;
    }    

    /**
     * @brief Sets object to be deleted
     * @param timer_s time to deletion
     */
    void Destroy(float timer_s=0.f) {
        if (!toBeDeleted && body->GetType() != b2_staticBody) {
            destroyList.push_back(std::make_pair(timer_s, this));
            toBeDeleted = true;
        }
       
    }

    /**
     * @brief Gives score if destroyed, resets
     * @return score to add
     */
    float transferScore() {
        if (!toBeDeleted) return 0;
        float oldScore = score;
        score = std::min(score, FLT_MIN);
        return oldScore;
    }

    /**
     * @brief Takes damage, plays sound
     * @param dmg damage taken
     * @return true if destroyed
     */
    virtual bool TakeDamage(float dmg) {
        if (MaxHP == FLT_MAX) return false;
        CurrentHP = std::max(0.0f, CurrentHP - dmg);

        checkDamage();
 
        if (dmg > 30.0f) {
            playSound(soundType::damage);
        } else if (dmg > 1.0f) {
            playSound(soundType::collision);
        }
        return CurrentHP <= 0;
    }

    virtual void checkDamage(){}
    virtual void setDestroyTexture(){}

    /**
     * @brief Delete object in timer_s seconds (deleted by Level).
     * @brief Objects need to be deleted between steps
     * @brief and sounds take time to finish.
     * @param timer_s time to deletion
     */
    virtual void updateTexture(float deltaTime) = 0;

    b2Body* getBody() { return body; }
    float getScore() { return score; }
    void setScore(float newScore) { score = newScore; }
    float getMaxHP() { return MaxHP; }
    float getHP() { return CurrentHP; }
    sf::Sprite& getSprite() { return sprite; }
    bool getDisableOnDestroy() {return disableOnDestroy;}
    bool getHasDestroyTexture() {return hasDestroyTexture;}
    constexpr const static float speedDamageMultiplier = 7.0f;  // tune this value
    static std::list< std::pair< float, Object* > > destroyList;  // <timer, object>

protected :
    b2Body* body;
    sf::Sprite sprite;

    std::vector<std::pair<std::string, float>> normalTextures;
    std::vector<std::pair<std::string, float>> damageTextures;

    std::vector<sf::Sound> damageSounds; 
    std::vector<sf::Sound> collisionSounds;
    std::vector<sf::Sound> destroySounds;
    std::map<std::string, sf::Sound> otherSoundsMap;

    float MaxHP;
    float CurrentHP;
    float score = 0;
    size_t currentTextureIdx = 0;
    float animationTimer = 0.0f;

    bool isDamaged = false;
    bool toBeDeleted = false;
    bool disableOnDestroy = true; 
    bool hasDestroyTexture = false;

};

std::list< std::pair< float, Object* > > Object::destroyList;

class ObjectCollisions : public b2ContactListener
{
    /**
     * @brief Handles collisions between Objects.
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
        Object* object;

        if (bodyData1) {
            object = static_cast<Object*>(bodyData1);
            object->TakeDamage(dmg);
        }
        if (bodyData2) {
            object = static_cast<Object*>(bodyData2);
            object->TakeDamage(dmg);
        }
    }
};

/**
 * @brief Raycasting for explosions.
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
