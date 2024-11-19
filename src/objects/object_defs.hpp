#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

#ifndef OBJECT_PHYSICS_HPP
#define OBJECT_PHYSICS_HPP

namespace ObjectDefs
{

    struct ObjectDefaults
    {
        b2BodyDef bodyDef;   
        sf::Sprite sprite;
        std::unique_ptr<b2Shape> shape;
        float density;
        float hp;
        float pixel_per_meter = 40.0f;
    };

    b2BodyDef GetBodyDef(b2BodyType type, float x=0, float y=0)
    {
        b2BodyDef bodyDef;
        bodyDef.type = type;
        bodyDef.position.Set(x, y);
        return bodyDef;
    }

    std::unique_ptr<b2CircleShape> CreateShape (float radius_m) {
        auto shape = std::unique_ptr<b2CircleShape>();
        shape->m_radius = radius_m;
        return shape;
    }

    std::unique_ptr<b2PolygonShape> CreateShape (float width_m, float height_m){
        auto shape = std::unique_ptr<b2PolygonShape>();
        shape->SetAsBox(width_m/2, height_m/2);
    }

    float CalculateHP(float baseHP, float radius_m) {     
        float area = b2_pi * radius_m * radius_m;
        return baseHP * area;
    }

    float CalculateHP(float baseHP, float width_m, float height_m) {
        float area = width_m * height_m;
        return baseHP * area;
    }

     sf::Sprite CreateSprite(float width_px, float height_px, const sf::Texture& texture)
    {
        sf::Sprite sprite(texture);
        float scale_w = width_px / texture.getSize().x;
        float scale_h = height_px / texture.getSize().y;
        sprite.setScale(scale_w, scale_h);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        return sprite;
    }
}

#endif

/////////////////////////////////////////////////////////
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

