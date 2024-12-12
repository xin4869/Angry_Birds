#ifndef VISUAL_GAME_RENDER_HPP
#define VISUAL_GAME_RENDER_HPP

#include <fstream>
#include <vector>
#include <box2d/box2d.h>
#include "../level.hpp"
#include "../objects/object_defs.hpp"
#include "../slingshot.hpp"


class GameRender{
public: 
    GameRender(sf::RenderWindow& game_window): window(game_window) {
        init();
        for (size_t i=0; i<trajectoryPoints; i++) {
            trajectorySprites.push_back(ObjectDefs::CreateSprite(TextureManager::getTexture("cloud")));
        }
    }

    /**
     * @brief Sets game bounds based on window size
     */
    void init() {
        // correct scaling
        std::cout << "size: " << window.getSize().x << ", " << window.getSize().y << std::endl;
        float x = window.getSize().x / ObjectDefs::pixel_per_meter;
        float y = window.getSize().y / ObjectDefs::pixel_per_meter;
        gameXBounds.Set(0, x);
        gameYBounds.Set(0, y);
        setCenter(0, 0.35f * y);
    }

    /**
     * @brief Renders the level on screen.
     * @param level render this level
     */
    void renderGame(Level& level) {
        Slingshot& ss = level.getSlingshot();
        renderSprite(ss.getSprite(), ss.getPos(), 0);

        for (auto i: level.getBirds()) {
            renderObject(i);
        }
        for (auto i: level.getPigs()) {
            renderObject(i);
        }
        for (auto i: level.getBlocks()) {
            renderObject(i);
        }
        
        if (level.getDragging()) drawTrajectory(level.getCurrentBird(),
                level.getSlingshot().getLaunchImpulse(level.getCurrentBird()), level.getGravity());

        renderGround(level.getGround());
    }
    
    void setXBounds(b2Vec2 bounds) { gameXBounds = bounds; }
    void setXBounds(float x, float y) { gameXBounds.Set(x, y); }
    void setYBounds(b2Vec2 bounds) { gameYBounds = bounds; }
    void setYBounds(float x, float y) { gameYBounds.Set(x, y); }
    
    /**
     * @brief Sets the center of game bounds such that bounds size stays the same
     * @param center new center point
     */
    void setCenter(b2Vec2 center) {
        float dx = gameXBounds.y - gameXBounds.x;
        float dy = gameYBounds.y - gameYBounds.x;

        setXBounds(center.x - dx / 2.0f, center.x + dx / 2.0f);
        setYBounds(center.y - dy / 2.0f, center.y + dy / 2.0f);
    }
    void setCenter(float x, float y) { setCenter(b2Vec2(x, y)); }

    /**
     * @brief Transforms a game position to screen position. Considers both bounds.
     * @param gamePos transform this
     * @return sf::Vector2f screen pos
     */
    sf::Vector2f toScreenPos(const b2Vec2& gamePos) const {
        float t = (gamePos.x - gameXBounds.x) / (gameXBounds.y - gameXBounds.x);
        float x = window.getSize().x * t;
        t = (gamePos.y - gameYBounds.x) / (gameYBounds.y - gameYBounds.x);
        float y = window.getSize().y * (1-t);
        return sf::Vector2f(x, y);
    }

    /**
     * @brief Transforms a screen position to game position. Considers both bounds.
     * @param screenPos transform this
     * @return b2Vec2 game position
     */
    b2Vec2 toGamePos(const sf::Vector2f& screenPos) const {
        float t = screenPos.x / window.getSize().x;
        float x = gameXBounds.x + (gameXBounds.y - gameXBounds.x) * t;
        t = screenPos.y / window.getSize().y;
        float y = gameYBounds.x + (gameYBounds.y - gameYBounds.x) * (1-t);
        return b2Vec2(x, y);
    }
   
private:
    sf::RenderWindow& window;
    const float radToDeg = 180.0f / M_PI;
    b2Vec2 gameXBounds;  // minX, maxX
    b2Vec2 gameYBounds;  // minY, maxY
    std::vector<sf::Sprite> trajectorySprites;
    size_t trajectoryPoints = 20;

    /**
     * @brief Renders object on screen.
     * @param object render this
     */
    void renderObject(Object* object) const {
        if (!object->getBody()->IsEnabled()) return;
        renderSprite(object->getSprite(), object->getBody()->GetPosition(), -object->getBody()->GetAngle() * radToDeg);
    }

    /**
     * @brief Renders a sprite on screen
     * @param sprite Sprite to render
     * @param gamePos position in game
     * @param rotDeg rotation in game in degrees
     */
    void renderSprite(sf::Sprite& sprite, const b2Vec2& gamePos, float rotDeg) const {
        float scale = ObjectDefs::pixel_per_meter / ObjectDefs::default_pixel_per_meter;
        sprite.setScale(sf::Vector2f(scale, scale));
        sprite.setPosition(toScreenPos(gamePos));
        sprite.setRotation(rotDeg);
        window.draw(sprite);
    }

    /**
     * @brief Draws the trajectory an object will take after an impulse.
     * @param object Draw this object's trajectory
     * @param impulse based on this impulse
     * @param gravity and this gravity
     */
    void drawTrajectory(Object* object, b2Vec2 impulse, b2Vec2 gravity) {
        if (object == nullptr) return;

        for (size_t i=0; i<trajectorySprites.size(); i++) {
            b2Vec2 vel = (1/object->getBody()->GetMass()) * impulse;
            float dt = 0.1f * (i+1);
            float x = object->getBody()->GetPosition().x + vel.x * dt + gravity.x / 2.0f * dt * dt;
            float y = object->getBody()->GetPosition().y + vel.y * dt + gravity.y / 2.0f * dt * dt;
            renderSprite(trajectorySprites[i], b2Vec2(x, y), 0);
        }
    }


    // void renderGround(const std::unique_ptr<Ground>& ground) const {
    //     if (!ground) return;
    //     b2Vec2 bodyPos = ground->getBody()->GetPosition();   
    //     std::cout << "Ground pos: " << bodyPos.x << ", " << bodyPos.y << std::endl;
    //     sf::Vector2f windowPos = toScreenPos(bodyPos);
    //     std::cout << "Window pos: " << windowPos.x << ", " << windowPos.y << std::endl;
    //     ground->getGroundShape().setPosition(windowPos.x, windowPos.y);
    //     window.draw(ground->getGroundShape());
    // }

    void renderGround(const std::unique_ptr<Ground>& ground) const {
        if (!ground) return;
        sf::ConvexShape groundShape;
        const std::vector<b2Vec2>& vertices = ground->getVertices();
        
        groundShape.setOrigin(toScreenPos(ground->getBody()->GetPosition()));
        groundShape.setPosition(toScreenPos(ground->getBody()->GetPosition()));
        
        groundShape.setPointCount(vertices.size());
        for (size_t i = 0; i < vertices.size(); ++i) {
            groundShape.setPoint(i, toScreenPos(vertices[i]));
        }

        groundShape.setTexture(&TextureManager::getTexture("ground"));

        window.draw(groundShape);
    }
};

#endif
