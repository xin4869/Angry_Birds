#ifndef GAME_TEXT_HPP
#define GAME_TEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>



class GameText {
public: 
    GameText(const std::string& fontPath, int size, const sf::Color& color, 
        const sf::Color& outlineColor, const sf::Vector2f& position, const std::string& text) {
            if (!font.loadFromFile(fontPath)) {
                throw std::runtime_error("Failed to load font");
            }
            textObject.setFont(font);
            textObject.setCharacterSize(size);
            textObject.setFillColor(color);
            textObject.setOutlineColor(outlineColor);
            textObject.setPosition(position);
            textObject.setString(text);
        }
    GameText() {}

    GameText(int size, const sf::Vector2f& position, const std::string& text) {
            if (!font.loadFromFile("assets/font/angrybirds.ttf")) {
                throw std::runtime_error("Failed to load font");
            }
            textObject.setFont(font);
            textObject.setFillColor(sf::Color::White);
            textObject.setOutlineColor(sf::Color::Black);
            textObject.setCharacterSize(size);
            textObject.setPosition(position);
            textObject.setString(text);
    }
    void setScale(float x, float y) {
        textObject.setScale(x, y);
    }

    void setString(const std::string& text) {
        textObject.setString(text);
    }

    void setPosition(const sf::Vector2f& position) {
        textObject.setPosition(position);
    }

    sf::Vector2f getPosition() const {
        return textObject.getPosition();
    }

    void setColor(const sf::Color& color) {
        textObject.setFillColor(color);
    }
    void setSize(size_t size) {
        textObject.setCharacterSize(size);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(textObject);
    }
private:
    sf::Text textObject;
    sf::Font font;
};

#endif