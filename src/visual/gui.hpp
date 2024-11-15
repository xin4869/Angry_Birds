#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#ifndef GUI_HPP
#define GUI_HPP

class GUI {
public:
    GUI() {}
    void initialize(){
        loadFont();
        setupTexts();
        setupMenu();
    }
    void update(int score, int birdsLeft){
        scoreText.setString("Score:" + std::to_string(score));
        birdsLeftText.setString("Birds left:" + std::to_string(birdsLeft));
    }

    void draw(sf::RenderWindow& window){
        window.draw(scoreText);
        window.draw(birdsLeftText);
    }

    void drawMenu(sf::RenderWindow& window){
        window.draw(menuBackground);
        window.draw(startGameText);
    }

    bool isStartButtonClicked(float mouseX, float mouseY) {
        return startGameText.getGlobalBounds().contains(mouseX, mouseY);
    }
    
private:
    sf::Font regularFont;
    sf::Font boldFont;

    sf::Text scoreText;
    sf::Text birdsLeftText;
    sf::Text startGameText;

    sf::RectangleShape menuBackground;
    

    void loadFont() {
        if (!regularFont.loadFromFile("assets/font/arial-font/arial.ttf")) {
            std::cout << "Error loading font" << std::endl;
        }

        if (!boldFont.loadFromFile("assets/font/arial-font/G_ari_bd.TTF")) {
            std::cout << "Error loading font" << std::endl;
        }
        
    }
    void setupTexts(){
        scoreText.setFont(boldFont);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(10, 10);

        birdsLeftText.setFont(regularFont);
        birdsLeftText.setCharacterSize(24);
        birdsLeftText.setFillColor(sf::Color::Black);
        birdsLeftText.setPosition(20, 10);

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