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
    virtual ~Object() { body->GetWorld()->DestroyBody(body); }

    Object(
        b2World* world,
        b2BodyDef* bodyDef,
        b2Shape* shape,
        float density,
        float x,
        float y,
        std::vector<std::pair<std::string, float>> textureDefs, 
        std::vector<std::pair<std::string, float>> damageTextureDefs,
        std::vector<std::string> destroySoundNames,
        std::vector<std::string> collisionSoundNames,
        std::vector<std::string> damageSoundNames,
        std::vector<std::string> otherSounds,
        float hp,
        float rotation=0.0f
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

        if (normalTextures.size() > 0) {
            const sf::Texture& txt = TextureManager::getTexture(normalTextures[0].first);
            sprite = ObjectDefs::CreateSprite(txt);
        }

        bodyDef->position.Set(x, y);
        bodyDef->angle = M_PI / 180.0f * rotation;
        body = world->CreateBody(bodyDef);
        b2Fixture* fix = body->CreateFixture(shape, density);
        
        // tune these
        body->SetAngularDamping(0.3f);
        fix->SetFriction(0.4f);

        body->SetTransform(b2Vec2(x,y), body->GetAngle());
        body->GetUserData().pointer = (uintptr_t)this;
    }

    Object(b2World* world, float x, float y, ObjectDefs::ObjectDefaults* defaults, float rotation=0.0f) :
        Object(world, &defaults->bodyDef, defaults->shape.get(), defaults->density,
            x, y, defaults->normalTextures, defaults->damageTextures, defaults->soundNames, defaults->maxHp, rotation) {}
    
    bool playSound(const std::string& name)
    {
        if (otherSoundsMap.find(name) == otherSoundsMap.end()) return false;
        otherSoundsMap[name].play();
        return true;
    }


    bool playSound(soundType sound_type) {

        std::vector<sf::Sound>& target_list = {};
        switch (sound_type)
        {
            case soundType::destroy:
                target_list = destroySounds;
                break;
            case soundType::collision:
                target_list = collisionSounds;
                break;
            case soundType::damage:
                target_list = damageSounds;
                break;
            
        default:
            return false;
        }

        size_t idx = rand() % target_list.size();
        target_list[idx].play();
        return true;
    }
       
    

    void Destroy(float timer_s=0.f) {
        if (!toBeDeleted) {
            destroyList.push_back(std::make_pair(timer_s, this));
            toBeDeleted = true;
        }
       
    }
   
   /**
    * @brief Overridden in subclasses. Set functionality there.
    * @param dmg damage taken
    * @return true if killed
    */
    virtual bool TakeDamage(float dmg) = 0;

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
    void setOut() {out = true;}
    bool isOut() {return out;}
    float getMaxHP() { return MaxHP; }
    float getHP() { return CurrentHP; }
    sf::Sprite& getSprite() { return sprite; }
    bool getDisableOnDestroy() {return disableOnDestroy;}
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

    bool isDamaged = false;
    bool toBeDeleted = false;
    bool out = false;
    bool disableOnDestroy = true; 

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
            // set special value for score to recognize and only count score once
            if (killed && object->getScore() > FLT_MIN) {
                scoreToAdd += object->getScore();
                object->setScore(FLT_MIN);
            }
        }
        if (bodyData2) {
            object = static_cast<Object*>(bodyData2);
            killed = object->TakeDamage(dmg);
            if (killed && object->getScore() > FLT_MIN) {
                scoreToAdd += object->getScore();
                object->setScore(FLT_MIN);
            }
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
