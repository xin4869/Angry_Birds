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

    //switch status, button texture when cursor is on / off the button
    virtual void mouseHover(sf::Vector2i cursor){
        if (!active) {
            if (sprite -> getGlobalBounds().contains(cursor.x, cursor.y)) {
                active = true;
                sprite->setTexture(active_texture);
            }
        } else {
            if (!sprite -> getGlobalBounds().contains(cursor.x, cursor.y)) {
                active = false;
                sprite->setTexture(inactive_texture);
            }
        }
    }

protected:
    sf::Sprite* sprite = nullptr;
    sf::Texture active_texture;
    sf::Texture inactive_texture;
    bool active;
};


// derived class of Buttons: option buttons
class OptionButtons: public Buttons {
public:
//option buttons do not change texture during mouse hovering
    virtual void mouseHover(sf::Vector2i cursor) override {
        if (!active) {
            if (sprite -> getGlobalBounds().contains(cursor.x, cursor.y)) {
                active = true;
            }
        } else {
            if (!sprite -> getGlobalBounds().contains(cursor.x, cursor.y)) {
                active = false;
            }
        }
    }
// change texture when selected/de-selected
    void switchTexture() {
        if (selected) {
            sprite -> setTexture(inactive_texture);
        } else {
            sprite -> setTexture(active_texture);
        }
        selected =! selected;
    }

protected:
    bool selected = false;
};
//derived class of OptionButtons: volume slider button
class VolumeSlider: public OptionButtons {
public:
    
    bool isGrabbed() {
        return grabbed;
    }

    void grabSlider() {
        grabbed = true;
    }

    void releaseSlider() {
        grabbed = false;
    }

    void updateMinMax(sf::RenderWindow& window) {
        min_x_pos = window.getSize().x * min_x_ratio;
        max_x_pos = window.getSize().y * max_x_ratio;
    }

    void moveSlider(sf::RenderWindow& window) {
        // slider should move only horizontally
        setPosition(sf::Mouse::getPosition(window).x, sprite->getPosition().y);
        
        //make sure slider move within boundary
        if (sprite->getPosition().x < min_x_pos) {
            sprite->setPosition(min_x_pos, sprite->getPosition().y);
        } else if (sprite->getPosition().x > max_x_pos) {
            sprite->setPosition(max_x_pos, sprite->getPosition().y);
        }
    }

    void mouseHover(sf::Vector2i cursor) {
        if(!active && sprite -> getGlobalBounds().contains(cursor.x, cursor.y)) {
            active = true;
        } else {
            active = false;
        }
    }



private:
    bool grabbed = false; 
    float min_x_pos;
    float max_x_pos;
    float min_x_ratio = 687.0f/1280.0f;
    float max_x_ratio = 839.0f/1280.0f;

};


#endif