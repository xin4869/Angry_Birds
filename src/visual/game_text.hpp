#ifndef GAME_TEXT_HPP
#define GAME_TEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>


/**
 * @brief Represents a visual text object.
 */
class GameText {
public: 
    GameText(sf::Font font, int size, const sf::Color& color, const sf::Color& outlineColor, const sf::Vector2f& position, const std::string& text):
        defaultPosition(position) {
            textObject.setFont(font);
            textObject.setCharacterSize(size);
            textObject.setFillColor(color);
            textObject.setOutlineColor(outlineColor);
            textObject.setOutlineThickness(2);
            textObject.setPosition(defaultPosition);
            textObject.setString(text);
        }

    GameText() {}

    GameText(int size, const sf::Vector2f& position, const std::string& text, 
        const sf::Color& fillColor = sf::Color::White, const sf::Color& outlineColor = sf::Color::Black): 
            defaultPosition(position) {
            if (defaultFont == nullptr) {
                throw std::runtime_error("Default font is not set");
            }
            textObject.setFont(*defaultFont);
            textObject.setFillColor(fillColor);
            textObject.setOutlineColor(outlineColor);
            textObject.setOutlineThickness(2);
            textObject.setCharacterSize(size);
            textObject.setPosition(defaultPosition);
            textObject.setString(text);
    }
    
    // void setScale(float x, float y) {
    //     textObject.setScale(x, y);
    // }

    void setString(const std::string& text) {
        textObject.setString(text);
    }

    static void setDefaultFont(sf::Font* font){
        defaultFont = font;
    }

    void setDefaultPosition(float x, float y) {
        defaultPosition = sf::Vector2f(x,y);
        textObject.setPosition(x,y);
    }

    void updatePosition(float scaleX, float scaleY) {
        float newX = defaultPosition.x * scaleX;
        float newY = defaultPosition.y * scaleY;
        textObject.setPosition(newX, newY);
    }

    void setColor(const sf::Color& color) {
        textObject.setFillColor(color);
    }
    void setSize(size_t size) {
        textObject.setCharacterSize(size);
    }

    void updateSize (float scaleX, float scaleY) {
        textObject.setScale(scaleX, scaleY);
    }

    void draw(sf::RenderWindow& window) {
        if (textObject.getFont() == nullptr) {
            throw std::runtime_error("Font is not set");
        }
        window.draw(textObject);
    }

private:
    sf::Text textObject;
    static inline sf::Font* defaultFont = nullptr;
    sf::Vector2f defaultPosition;
};

#endif