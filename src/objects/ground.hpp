#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "../visual/texture_manager.hpp"
#include "../objects/object_defs.hpp"

#ifndef OBJECT_GROUND_HPP
#define OBJECT_GROUND_HPP


class Ground
{
public:
    Ground(b2World* world, const std::vector<b2Vec2>& vertices): m_vertices(vertices) {
        b2Vec2 centerPos = calculateCenter(vertices);
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(centerPos.x, centerPos.y);
        body = world->CreateBody(&bodyDef);

        b2ChainShape chainShape;
        chainShape.CreateChain(vertices.data(), vertices.size(), vertices.front(), vertices.back());

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &chainShape;
        fixtureDef.density = 0.0f;
        // fixtureDef.restitution = 0.0f;
        fixtureDef.friction = 0.3f;
        // fixtureDef.isSensor = true;
        body->CreateFixture(&fixtureDef);
    }

    // std::vector<std::pair<sf::Sprite, b2Vec2>>&  getPairs() { return pairs; }
    // sf::ConvexShape& getGroundShape() { return groundShape; }
    std::vector<b2Vec2>& getVertices() { return m_vertices; }
    b2Body* getBody() { return body; }

protected:
    // std::vector<std::pair<sf::Sprite, b2Vec2>> pairs;
    std::vector<b2Vec2> m_vertices;
    // sf::ConvexShape groundShape;
    b2Body* body;

    b2Vec2 calculateCenter(const std::vector<b2Vec2>& vertices) {
        float sumX = 0.f, sumY = 0.f;
        for (const auto& vertex : vertices) {
            sumX += vertex.x;
            sumY += vertex.y;
        }
        return b2Vec2(sumX / vertices.size(), sumY / vertices.size());
    }

    // void setGroundShape(const std::vector<b2Vec2>& vertices) {
    //     // Create a convex shape for the ground (polygon based on vertices)
    //     groundShape.setPointCount(vertices.size());
        
    //     for (size_t i = 0; i < vertices.size(); ++i) {
    //         groundShape.setPoint(i, sf::Vector2f(vertices[i].x * ObjectDefs::pixel_per_meter, vertices[i].y * ObjectDefs::pixel_per_meter));
    //     }
        
    //     groundShape.setTexture(&TextureManager::getTexture("ground")); // Set the ground color (optional)
    // }


    // void setTiles(const std::vector<b2Vec2>& vertices) {

    //     b2Vec2 minPos = vertices[0];
    //     b2Vec2 maxPos = vertices[0];
    //     for (const auto& vertex : vertices) {
    //         minPos = b2Vec2(std::min(minPos.x, vertex.x), std::min(minPos.y, vertex.y));
    //         maxPos = b2Vec2(std::max(maxPos.x, vertex.x), std::max(maxPos.y, vertex.y));
    //     }

    //     const sf::Texture& texture = TextureManager::getTexture("ground");
    //     float tileWidth = texture.getSize().x / ObjectDefs::pixel_per_meter;
    //     float tileHeight = texture.getSize().y / ObjectDefs::pixel_per_meter;

    //     for (float x = minPos.x; x < maxPos.x; x += tileWidth) {
    //         for (float y = minPos.y; y < maxPos.y; y += tileHeight) {
    //             sf::Sprite tileSprite(texture);
    //             pairs.emplace_back(tileSprite, b2Vec2(x, y));
    //         }
    //     }
    // }
};


#endif
