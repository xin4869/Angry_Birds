#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef VISUAL_BUTTON_HPP
#define VISUAL_BUTTON_HPP

class Buttons {
public:
    Buttons(){
        sprite = new sf::Sprite;
        active = false;
    }

    ~Buttons(){
        delete sprite;
    }
  
    void setTexture(std::string active_path, std::string inactive_path) {
        if(!active_texture.loadFromFile(active_path)) {
            std::cout <<"(active) button texture loading fail!"<< active_path;
        }
        if(!inactive_texture.loadFromFile(inactive_path)) {
            std::cout<<"(inactive) button texture loading fail!"<< inactive_path;
        }

        sprite->setTexture(inactive_texture);
        sprite->setOrigin(active_texture.getSize().x/2, active_texture.getSize().y/2);

    }
    
    void setTexture(std::string path) {
        if(!active_texture.loadFromFile(path)) {
            std::cout <<"button texture loading fail!"<< path;
        }
    }

    sf::Sprite* getSprite(){
        return sprite;
    }

    virtual void mouseHover(sf::Vector2i cursor){
        if (!active) {
            if (sprite -> getGlobalBounds().contains(cursor.x, cursor.y)) {
                active = true;
                sprite->setTexture(active_texture);
            }
        } else {
            
        }
    }

protected:
    sf::Sprite* sprite = nullptr;
    sf::Texture& active_texture;
    sf::Texture& inactive_texture;
    bool active;
};

#endif