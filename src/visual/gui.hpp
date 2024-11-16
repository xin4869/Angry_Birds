#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "visual/buttons.hpp"

#ifndef GUI_HPP
#define GUI_HPP

class GUI {
public:
    GUI(sf::RenderWindow& game_window): window(game_window) {}
    void init(){
        initFont();
        setupMenu();
    }

    void loadTexture (sf::Texture& texture, const std::string& path) {
        if (!texture.loadFromFile(path)) {
            std::cout << "Texture loading failed!\n";
        }
    }

    void initTextures(){
        loadTexture(background_texture, "assets/textures/background.png" );
        background_sprite.setTexture(background_texture);

    }

    

    

    void updateText(int score){
        current_score.setString("Score:" + std::to_string(score));
        final_score.setString("Your score: " + std::to_string(score));
    }

    void draw(sf::RenderWindow& window){
        window.draw(score);
    }

    void drawMenu(sf::RenderWindow& window){
        window.draw(menuBackground);
        window.draw(startGameText);
    }

    bool isStartButtonClicked(float mouseX, float mouseY) {
        return startGameText.getGlobalBounds().contains(mouseX, mouseY);
    }
    
private:
    sf::RenderWindow& window;
    sf::Font font;

    sf::Text current_score;
    sf::Text final_score;
    sf::Text startGameText;

    sf::RectangleShape menuBackground;

    sf::Sprite background_sprite;
    sf::Texture background_texture;
    sf::Sprite pause_sprite;
    sf::Texture pause_texture;
    sf::Sprite help_sprite;
    sf::Texture help_texture;

    sf::Texture lvl1_texture;
    sf::Texture lvl2_texture;
    sf::Texture lvl3_texture;
    sf::Texture  
    

    void initFont(){
        if (!font.loadFromFile("assets/font/angrybirds.ttf")) {
            std::cout << "Font loading failed!" << std::endl;
        }

        scoreText.setFont(font);
        scoreText.setCharacterSize(35);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(10, 10);

    }
    void setupMenu(){
        menuBackground.setSize(sf::Vector2f(200, 100));
        menuBackground.setFillColor(sf::Color(200,200,200));
        menuBackground.setPosition(10, 10);

        startGameText.setFont(boldFont);
        startGameText.setCharacterSize(30);
        startGameText.setFillColor(sf::Color::Black);
        startGameText.setString("Start Game");
        startGameText.setPosition(450, 350);
    }
};

#endif // GUI_HPP