#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "visual/buttons.hpp"
#include "visual/game_render.hpp"


#ifndef GUI_HPP
#define GUI_HPP

class GUI {
public:
    GUI(sf::RenderWindow& game_window): window(game_window) {}

    void init(){
        initFont();
        initTextures();
        initButtons();
        initFont();
    }

    void updateText(int score){
        current_score.setString("Score:" + std::to_string(score));
        final_score.setString("Your score: " + std::to_string(score));
    }

    void draw(sf::RenderWindow& window){
        //window.draw(score);
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
    

    Buttons play_bt;
    Buttons lv1_bt;
    Buttons lv2_bt;
    Buttons lv3_bt;

    Buttons help_bt;
    Buttons main_bt;

    
    void loadTexture (sf::Texture& texture, const std::string& path) {
        if (!texture.loadFromFile(path)) {
            std::cout << "Texture loading failed!\n";
        }
    }

    void initTextures(){
        loadTexture(background_texture, "assets/textures/background.png" );
        background_sprite.setTexture(background_texture);
    }

    void initButtons(){
        play_bt.setTexture("assets/textures/buttons/play.png")
        

    }


    void initFont(){
        if (!font.loadFromFile("assets/font/angrybirds.ttf")) {
            std::cout << "Font loading failed!" << std::endl;
        }

        scoreText.setFont(font);
        scoreText.setCharacterSize(35);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(10, 10);

    }


    void checkButtons() {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        play_bt.mouseHover(mouse_pos);
        lv1_bt.mouseHover(mouse_pos);
        lv2_bt.mouseHover(mouse_pos);
        lv3_bt.mouseHover(mouse_pos);

        help_bt.mouseHover(mouse_pos);
        setting_bt.mouseHover(mouse_pos);
        main_bt.mouseHover(mouse_pos);
    }

   

    
};

#endif // GUI_HPP