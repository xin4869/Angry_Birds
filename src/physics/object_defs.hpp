#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

#ifndef _AB_PHYSICS_DEF_
#define _AB_PHYSICS_DEF_

/**
 * @brief this is here to keep textures in memory.
 * @brief won't work otherwise.
 * 
 */
class Textures
{
public:
    sf::Texture circleTexture;
    sf::Texture squareTexture;

    Textures(std::string circlePath, std::string squarePath)
    {
        circleTexture.loadFromFile(circlePath);
        squareTexture.loadFromFile(squarePath);
    }
};

/**
 * @brief Convenience definitions for simpler object initialisation.
 * @brief Using not necessary.
 * 
 */
namespace ObjectDefs
{
    Textures textures("./assets/textures/circle.png", "./assets/textures/square.png");

    /**
     * @brief Get a Body Def object (used for physics objects)
     * 
     * @param type body type (static or dynamic)
     * @param x coordinate
     * @param y coordinate
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
     * @brief Get a Box Shape object (hitbox)
     * 
     * @param width
     * @param height 
     * @return b2PolygonShape 
     */
    b2PolygonShape GetBoxShape(float width, float height)
    {
        b2PolygonShape boxShape;
        boxShape.SetAsBox(width / 2, height / 2);
        return boxShape;
    }

    /**
     * @brief Get a Circle Shape object (hitbox)
     * 
     * @param radius 
     * @return b2CircleShape 
     */
    b2CircleShape GetCircleShape(float radius)
    {
        b2CircleShape circleshape;
        circleshape.m_radius = radius;
        return circleshape;
    }

    /**
     * @brief Get the Circle Sprite object
     * 
     * @param width sprite width in px
     * @param height sprite height in px
     * @param color sprite color
     * @return sf::Sprite 
     */
    sf::Sprite GetCircleSprite(float width, float height, sf::Color color=sf::Color::White)
    {
        auto size = textures.circleTexture.getSize();
        sf::Sprite sprite;
        sprite.setTexture(textures.circleTexture);
        sprite.setColor(color);
        sprite.setScale(width / size.x, height / size.y);
        return sprite;
    }

    sf::Sprite GetRectSprite(float width, float height, sf::Color color=sf::Color::White)
    {
        auto size = textures.squareTexture.getSize();
        sf::Sprite sprite;
        sprite.setTexture(textures.squareTexture);
        sprite.setColor(color);
        sprite.setScale(width / size.x, height / size.y);
        return sprite;
    }
}

#endif
