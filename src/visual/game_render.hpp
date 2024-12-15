#ifndef VISUAL_GAME_RENDER_HPP
#define VISUAL_GAME_RENDER_HPP

#include <fstream>
#include <vector>
#include <box2d/box2d.h>
#include "../level.hpp"
#include "../objects/object_defs.hpp"
#include "../slingshot.hpp"


/**
 * @brief Renders the game on screen.
 */
class GameRender{
public: 
    GameRender(sf::RenderWindow& game_window): window(game_window) {
        for (size_t i=0; i<trajectoryPoints; i++) {
            trajectorySprites.push_back(ObjectDefs::CreateSprite(TextureManager::getTexture("cloud")));
        }
        setBounds();
    }

    /**
     * @brief Sets game bounds based on window size
     */
    void setBounds() {
        // correct scaling
        std::cout << "size: " << window.getSize().x << ", " << window.getSize().y << std::endl;
        float x = window.getSize().x / ObjectDefs::pixel_per_meter;
        float y = window.getSize().y / ObjectDefs::pixel_per_meter;
        gameXBounds.Set(0, x);
        gameYBounds.Set(0, y);
        setCenter(0, 0.35f * y);
    }

    /**
     * @brief Checks if an object is in bounds
     * @param object 
     * @return true if in bounds
     */
    bool inBounds(Object* object) {
        b2Vec2 pos = object->getBody()->GetPosition();
        sf::Vector2f screenPos = toScreenPos(pos);
        if (screenPos.x > window.getSize().x || screenPos.x < 0) {
            return false;
        }
        return true;
    }

    /**
     * @brief Renders the level on screen.
     * @param level render this level
     */
    void renderGame(Level& level) {
        drawSlingshotBand(level);
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
        
        renderGrounds(level.getGrounds());
        
        if (level.getDragging()) drawTrajectory(level.getCurrentBird(),
                level.getSlingshot().getLaunchImpulse(level.getCurrentBird()), level.getGravity());
    }
    
    void setXBounds(b2Vec2 bounds) { gameXBounds = bounds; }
    void setXBounds(float x, float y) { gameXBounds.Set(x, y); }
    void setYBounds(b2Vec2 bounds) { gameYBounds = bounds; }
    void setYBounds(float x, float y) { gameYBounds.Set(x, y); }
    b2Vec2 getXBounds() { return gameXBounds; }
    b2Vec2 getYBounds() { return gameYBounds; }
    b2Vec2 getCenter() { return b2Vec2((gameXBounds.x + gameXBounds.y) / 2.0f, (gameYBounds.x + gameYBounds.y) / 2.0f); }
    
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
    std::vector<sf::Sprite> trajectorySprites;
    size_t trajectoryPoints = 30;
    b2Vec2 gameXBounds;  // minX, maxX
    b2Vec2 gameYBounds;  // minY, maxY

    /**
     * @brief Renders object on screen.
     * @param object render this
     */
    void renderObject(Object* object) const {
        if (!object->getBody()->IsEnabled() && !object->getHasDestroyTexture()) return;
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

    /**
     * @brief Renders grounds
     * @param grounds 
     */
    void renderGrounds(const std::vector<std::unique_ptr<Ground>>& grounds) const {
        sf::Texture& ground_texture = TextureManager::getTexture("ground");
        ground_texture.setRepeated(true);
        
        for (auto ground = grounds.begin(); ground != grounds.end(); ++ground) {
            if (!*ground) return;
            sf::ConvexShape groundShape;
            const std::vector<b2Vec2>& vertices = (*ground)->getVertices();
            
            groundShape.setPointCount(vertices.size());
            for (size_t i = 0; i < vertices.size(); ++i) {
                groundShape.setPoint(i, toScreenPos(vertices[i]));
            }

            groundShape.setTexture(&ground_texture);
            sf::IntRect textureRect(0, 0, groundShape.getGlobalBounds().width, groundShape.getGlobalBounds().height);
            groundShape.setTextureRect(textureRect);

            window.draw(groundShape);
        }

        // In renderGround function, after drawing the ConvexShape
        // Draw Box2D shape for debugging
        // sf::VertexArray lines(sf::LineStrip, vertices.size() + 1);
        // for (size_t i = 0; i < vertices.size(); ++i) {
        //     lines[i].position = toScreenPos(vertices[i]);
        //     lines[i].color = sf::Color::Red;
        // }
        // lines[vertices.size()] = lines[0]; // Close the shape
        // window.draw(lines);
    }

    /**
     * @brief Draws both slingshot bands
     * @param level 
     */
    void drawSlingshotBand(Level& level) {
        if (!level.getDragging() || !level.getCurrentBird()) return;
        
        b2Vec2 start = level.getCurrentBird()->getBody()->GetPosition();
        b2Vec2 end = level.getSlingshot().getPos() + b2Vec2(0, 2);
        b2Vec2 end1 = end + b2Vec2(0.6f, -0.3f);
        b2Vec2 end2 = end + b2Vec2(-0.6f, -0.3f);
        drawBand(start, end1);
        drawBand(start, end2);
    }

    /**
     * @brief Draws a band
     * @param start start game pos
     * @param end end game pos
     */
    void drawBand(b2Vec2 start, b2Vec2 end) {
        b2Vec2 offset = end - start;
        sf::RectangleShape band1(sf::Vector2f(offset.Length() * 1.05f, std::min(0.6f / offset.Length(), 0.6f)));
        float angle = 90.0f;
        if (offset.x != 0) angle = -atan(offset.y / offset.x) * radToDeg;
        band1.setRotation(angle);
        band1.setFillColor(sf::Color(47, 24, 13));
        band1.setOrigin(band1.getSize() / 2.f);
        b2Vec2 bandPos = start + 0.5 * offset;
        float scale = ObjectDefs::pixel_per_meter;
        band1.scale(scale, scale);
        band1.setPosition(toScreenPos(bandPos));
        window.draw(band1);
    }
};

#endif
