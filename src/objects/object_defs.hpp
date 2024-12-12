#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <vector>

#ifndef OBJECT_PHYSICS_HPP
#define OBJECT_PHYSICS_HPP

namespace ObjectDefs
{
    float default_pixel_per_meter = 40;
    float pixel_per_meter = default_pixel_per_meter;

    struct ObjectDefaults
    {
        b2BodyDef bodyDef;   
        std::unique_ptr<b2Shape> shape;
        float density=0.0f;
        float maxHp;
        float spriteWidth;
        float spriteHeight;
        std::vector<std::pair<std::string, float>> normalTextures;
        std::vector<std::pair<std::string, float>> damageTextures;
        std::vector<std::string> destroySoundNames;
        std::vector<std::string> collisionSoundNames;
        std::vector<std::string> damageSoundNames;
        std::vector<std::string> otherSounds;
    };

    /**
     * @brief Gets a bodydef for objects
     * @param type body type (static, dynamic)
     * @param x game pos
     * @param y game pos
     * @return b2BodyDef
     */
    b2BodyDef GetBodyDef(b2BodyType type, float x=0, float y=0)
    {
        b2BodyDef bodyDef;
        bodyDef.type = type;
        bodyDef.position.Set(x, y);
        return bodyDef;
    }

    /**
     * @brief Creates a circle shape (collider)
     * @param radius_m circle radius (m)
     * @return std::unique_ptr<b2CircleShape>
     */
    std::unique_ptr<b2CircleShape> CreateShape (float radius_m) {
        auto shape = std::make_unique<b2CircleShape>();
        shape->m_radius = radius_m;
        return shape;
    }

    /**
     * @brief Creates a rectangle shape (collider)
     * @param width_m width (m)
     * @param height_m height (m)
     * @return std::unique_ptr<b2PolygonShape> 
     */
    std::unique_ptr<b2PolygonShape> CreateShape (float width_m, float height_m){
        auto shape = std::make_unique<b2PolygonShape>();
        shape->SetAsBox(width_m/2, height_m/2);
        return shape;
    }

    /**
     * @brief Creates a triangle shape (collider)
     * @param base_m base length (m)
     * @param height_m height (m)
     * @param leftOriented
     * @return std::unique_ptr<b2PolygonShape> 
     */
    std::unique_ptr<b2PolygonShape> CreateShapeTriangle(float base_m, float height_m, bool leftOriented) {
        auto shape = std::make_unique<b2PolygonShape>();
        b2Vec2 vertices[3];
        
        vertices[0] = b2Vec2(-base_m / 2.0f, -height_m / 2.0f);
        vertices[1] = b2Vec2(base_m / 2.0f, -height_m / 2.0f);
        if (leftOriented) {
            vertices[2] = b2Vec2(-base_m / 2.0f, height_m / 2.0f);
        } else {
            vertices[2] = b2Vec2(base_m / 2.0f, height_m / 2.0f);
        }
        shape->Set(vertices, 3);
        return shape;
    }

    /**
     * @brief Get circle HP scaled by area
     * @param baseHP HP when area == 1
     * @param radius_m circle radius
     * @return float HP
     */
    float CalculateHp(float baseHP, float radius_m) {     
        float area = b2_pi * radius_m * radius_m;
        return baseHP * area;
    }

    /**
     * @brief Get rectangle HP scaled by area
     * @param baseHP HP when area == 1
     * @param width_m width (m)
     * @param height_m height (m)
     * @return float HP
     */
    float CalculateHp(float baseHP, float width_m, float height_m) {
        float area = width_m * height_m;
        return baseHP * area;
    }

    /**
     * @brief Get triangle HP scaled by area
     * @param baseHP HP when area == 1
     * @param base_m base width (m)
     * @param height_m height (m)
     * @return float HP
     */
    float CalculateHpTriangle(float baseHP, float base_m, float height_m) {
        float area = base_m * height_m / 2;
        return baseHP * area;
    }

    sf::Sprite CreateSprite(const sf::Texture& texture)
    {
        sf::Sprite sprite(texture);
        // float scale_w = width_px / texture.getSize().x;
        // float scale_h = height_px / texture.getSize().y;
        // sprite.setScale(scale_w, scale_h);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        return sprite;
    }  
};

#endif

////////////////////////////////////////////////////////////////////////////////
/* 
Birds:
Density: 1.0
No HP

SpeedBirds: 
Density:0.81

BombBirds: 
Density: 1.45
---
Pigs:
Density: 1.0
HP: 100 (easier to destroy than blocks)
---
Ice:
Density: 0.8 (slightly less dense than water)
HP: 50 (weakest material)
---
Wood:
Density: 1.2 (wood typically floats on water)
HP: 150 (medium strength)
---
Stone:
Density: 2.6 (typical density of rock)
HP: 300 (hardest to break)

-----
Physics world dimension: 1 meter = 40 pixels

*/

