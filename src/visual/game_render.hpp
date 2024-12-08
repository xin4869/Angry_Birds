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
    }

    void init() {
        // correct scaling
        std::cout << "size: " << window.getSize().x << ", " << window.getSize().y << std::endl;
        float x = window.getSize().x / ObjectDefs::pixel_per_meter;
        float y = window.getSize().y / ObjectDefs::pixel_per_meter;
        gameXBounds.Set(0, x);
        gameYBounds.Set(0, y);
        setCenter(0, 10);
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
        //drawTrajectory();
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

    b2Vec2 toGamePos(const sf::Vector2i& screenPos) const {
        float t = (float)screenPos.x / (float)window.getSize().x;
        float x = lerp(gameXBounds.x, gameXBounds.y, t);
        t = (float)screenPos.y / (float)window.getSize().y;
        float y = lerp(gameYBounds.y, gameYBounds.x, t);
        return b2Vec2(x, y);
    }
   
private:
    sf::RenderWindow& window;
    const float radToDeg = 180.0f / M_PI;
    b2Vec2 gameXBounds;  // minX, maxX
    b2Vec2 gameYBounds;  // minY, maxY

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
        sprite.setPosition(toScreenPos(gamePos));
        sprite.setRotation(rotDeg);
        window.draw(sprite);
    }
};

#endif
