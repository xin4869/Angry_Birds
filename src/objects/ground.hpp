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

    std::vector<b2Vec2>& getVertices() { return m_vertices; }
    b2Body* getBody() { return body; }

protected:
    std::vector<b2Vec2> m_vertices;
    b2Body* body;

    b2Vec2 calculateCenter(const std::vector<b2Vec2>& vertices) {
        float sumX = 0.f, sumY = 0.f;
        for (const auto& vertex : vertices) {
            sumX += vertex.x;
            sumY += vertex.y;
        }
        return b2Vec2(sumX / vertices.size(), sumY / vertices.size());
    }
    
};


#endif
