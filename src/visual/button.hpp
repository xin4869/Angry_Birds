#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#ifndef VISUAL_BUTTON_HPP
#define VISUAL_BUTTON_HPP

class Button {
public:
    Button(const sf::Texture& texture): sprite(std::make_unique<sf::Sprite>()) {
        sprite->setTexture(texture);
    }

    void setScale(sf::Vector2f targetSize) {
        float scale_x = targetSize.x / getSize().x;
        float scale_y = targetSize.y / getSize().y;
        sprite->setScale(scale_x, scale_y);
    }

    sf::Vector2f getSize() const {
        sf::FloatRect bound = sprite->getGlobalBounds();
        return sf::Vector2f(bound.width, bound.height);
    }

    void setPosition(float x, float y) {
        sprite->setPosition(x,y);
    }

    sf::Vector2f getPosition() const {
        return sprite->getPosition();
    }


    void draw(sf::RenderWindow& window) {
        if (sprite) {
            window.draw(*sprite);
        }
    }

   //check if cursor is on this button
    
    bool isClicked(const sf::Vector2f& mousePos) const {
        return sprite->getGlobalBounds().contains(mousePos);
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

protected:
    std::unique_ptr<sf::Sprite> sprite;
    bool active = false;
};


#endif