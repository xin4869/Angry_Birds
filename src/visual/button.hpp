#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#ifndef VISUAL_BUTTON_HPP
#define VISUAL_BUTTON_HPP

class Button {
public:
    Button(const sf::Texture& texture) {
        sprite.setTexture(texture);     
    }

    Button() {}

    void setScale(sf::Vector2f targetSize) {
        float scale_x = targetSize.x / getSize().x;
        float scale_y = targetSize.y / getSize().y;
        sprite.setScale(scale_x, scale_y);
    }

    sf::Vector2f getSize() const {
        sf::FloatRect bound = sprite.getGlobalBounds();
        return sf::Vector2f(bound.width, bound.height);
    }

    void setDefaultPosition(float x, float y) {
        defaultPosition = sf::Vector2f(x,y);
        sprite.setPosition(x,y);
    }

    void updatePosition(float scaleX, float scaleY) {
        float newX = defaultPosition.x * scaleX;
        float newY = defaultPosition.y * scaleY;
        sprite.setPosition(newX, newY);
    }

    void draw(sf::RenderWindow& window) {
        if (active) {
            window.draw(sprite);
        }
    }
    
    bool isClicked(const sf::Vector2f& mousePos) const {
        return active && sprite.getGlobalBounds().contains(mousePos);
    }

    void activate() {
        if(!active) {
            active = true;
        }
    }

    void deactivate() {
        if(active) {
            active = false;
        }
    }

    bool isActive() const {
        return active;
    }

private:
    sf::Sprite sprite;
    bool active = false;
    sf::Vector2f defaultPosition;
};


#endif