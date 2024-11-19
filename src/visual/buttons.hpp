#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef VISUAL_BUTTON_HPP
#define VISUAL_BUTTON_HPP

class Buttons {
public:
    Buttons(){
        sprite = new sf::Sprite;
    }

    ~Buttons(){
        delete sprite;
    }

    void setPosition(float x, float y) {
        sprite->setPosition(x,y);
    }

    sf::Sprite* getSprite(){
        return sprite;
    }

    // set texture for dynamic buttons (texture can changed)
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
    // set texture for static buttons
    void setTexture(std::string path) {
        if(!active_texture.loadFromFile(path)) {
            std::cout <<"button texture loading fail!"<< path;
        }
    }

   //check if cursor is on this button
    bool mouseOn(float x, float y){
        if (sprite -> getGlobalBounds().contains(x, y)) {
            return true;
        } else {
            return false;
        }
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
    sf::Sprite* sprite = nullptr;
    sf::Texture active_texture;
    sf::Texture inactive_texture;
    bool active = false;
};




#endif