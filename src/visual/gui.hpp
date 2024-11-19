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
        initScore();
        initBackground();
        initButtons();
    }

    void updateScore(int score, int total){
        shot_score.setString("Score:" + std::to_string(score));
        total_score.setString("Total: " + std::to_string(total));
        final_score.setString("Score: " + std::to_string(total));
    }

    void updateBackground () {
        //lvl1, lvl2, lvl3, help, levels,win,lost
    }

    void drawHome(){
        window.draw(score);
    }
    void drawHelp(){}
    void drawLevels(){}    
    void drawGame(){}
    void drawWin(){}
    void drawLost(){}

    Buttons play_bt;
    Buttons help_bt;
    Buttons music_bt;

    Buttons ok_bt;

    Buttons lv1_bt;
    Buttons lv2_bt;
    Buttons lv3_bt;
    Buttons main_bt;

    Buttons levels_bt;
    Buttons replay_bt;
    Buttons next_bt;
    
private:
    sf::RenderWindow& window;

    sf::Font font;

    sf::Text shot_score;
    sf::Text total_score;
    sf::Text final_score;

    sf::Sprite background_sprite;
    sf::Texture home_texture;

    sf::Texture help_texture;
    sf::Texture levels_texture;
    sf::Texture lvl1_texture;
    sf::Texture lvl2_texture;
    sf::Texture lvl3_texture;
    sf::Texture win_texture;
    sf::Texture lost_texture;

    sf::Sprite info_sprite;
    sf::Texture info_texture;
   

    // ?????? animation, different kind of birds
    

    void initBackground(){
        //try ??
        if (!home_texture.loadFromFile("assets/textures/background.png")) {
            std::cout << "Texture loading failed!\n";
        }
        // load: all textures
        // info_sprite.setTexture(info_texture)
        background_sprite.setTexture(home_texture);
    }

    void initButtons(){
        play_bt.setTexture("assets/textures/buttons/play.png");
        help_bt.setTexture("assets/textures/buttons/help.png");
        music_bt.setTexture("assets/textures/buttons/music.png",
                            "assets/textures/buttons/no_music.png");

        ok_bt.setTexture("assets/textures/buttons/ok.png");

        lv1_bt.setTexture("assets/textures/buttons/lvl1.png");
        lv2_bt.setTexture("assets/textures/buttons/lvl2.png");
        lv3_bt.setTexture("assets/textures/buttons/lvl3.png");
        main_bt.setTexture("assets/textures/buttons/home.png");

        levels_bt.setTexture("assets/textures/buttons/level.png");
        replay_bt.setTexture("assets/textures/buttons/replay.png");
        next_bt.setTexture("assets/textures/buttons/next.png");
        
    }


    void initScore(){
        if (!font.loadFromFile("assets/font/angrybirds.ttf")) {
            std::cout << "Font loading failed!" << std::endl;
        }

        shot_score.setFont(font);
        shot_score.setCharacterSize(35);
        shot_score.setFillColor(sf::Color::White);
        shot_score.setOutlineColor(sf::Color::Black);
        shot_score.setString("");
        shot_score.setPosition(1200, 10);
             
        total_score.setFont(font);
        total_score.setCharacterSize(45);
        total_score.setFillColor(sf::Color::White);
        total_score.setOutlineColor(sf::Color::Black); 
        total_score.setString("");
        total_score.setPosition(1200,20);
           
        final_score.setFont(font);
        final_score.setCharacterSize(70);
        final_score.setFillColor(sf::Color::White);
        final_score.setOutlineColor(sf::Color::Black);
        final_score.setString("");
        final_score.setPosition(
            window.getSize().x * 0.5 - final_score.getGlobalBounds().width * 0.5,
            window.getSize().y * 0.55 - final_score.getGlobalBounds().height * 0.5);   
    }


};

#endif // GUI_HPP