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
        float base_hp;
    };

    b2BodyDef GetBodyDef(b2BodyType type, float x=0, float y=0)
    {
        b2BodyDef bodyDef;
        bodyDef.type = type;
        bodyDef.position.Set(x, y);
        return bodyDef;
    }

    std::unique_ptr<b2CircleShape> CreateShape (float radius) {
        auto shape = std::unique_ptr<b2CircleShape>();
        shape->m_radius = radius;
        return shape;
    }

    std::unique_ptr<b2PolygonShape> CreateShape (float width, float height){
        auto shape = std::unique_ptr<b2PolygonShape>();
        shape->SetAsBox(width/2, height/2);
    }

    float CalculateHP(float baseHP, const std::unique_ptr<b2CircleShape>& shape) {
        if (!shape) {
            std::cerr << "Invalid shape pointer" << std::endl;
            return baseHP;
        }
        float area = b2_pi * shape->m_radius * shape->m_radius;
        return baseHP * area;
    }

    float CalculateHP(float baseHP, const std::unique_ptr<b2PolygonShape>& shape) {
        if (!shape) {
            std::cerr << "Invalid shape pointer" << std::endl;
            return baseHP;
        }

        float area = 0.0f;
        int32 vertexCount = shape->m_count;
        for (int32 i = 0; i < vertexCount; ++i) {
            const b2Vec2& v1 = shape->m_vertices[i];
            const b2Vec2& v2 = shape->m_vertices[(i + 1) % vertexCount];
            area += (v1.x * v2.y - v2.x * v1.y);
        }
        area = std::abs(area) / 2.0f;

        return baseHP * area;
    }

     sf::Sprite CreateSprite(float width, float height, const sf::Texture& texture)
    {
        sf::Sprite sprite(texture);
        float scale_w = width / texture.getSize().x;
        float scale_h = height / texture.getSize().y;
        sprite.setScale(scale_w, scale_h);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        return sprite;
    }

/////////////////// Texture class necessary?/////////////////////////
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
*/
    class Textures
    {
    public:
        sf::Texture circleTexture;
        sf::Texture squareTexture;

        Textures(std::string circlePath, std::string squarePath)
        {
            // files don't load / aren't added when running tests. fix?
            if (!circleTexture.loadFromFile(circlePath))
            {
                circleTexture.create(64, 64);
            }
            if (!squareTexture.loadFromFile(squarePath))
            {
                squareTexture.create(64, 64);
            }
        }
    };

    Textures textures("./assets/textures/circle.png", "./assets/textures/square.png");


}

#endif
