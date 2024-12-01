#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <unordered_map>
#include "texture_manager.hpp"
#include "button.hpp"
#include "game_text.hpp"

#ifndef GUI_HPP
#define GUI_HPP



class GUI {
public:
    GUI(sf::RenderWindow& game_window): window(game_window) {}

    void init(){
        if (!font.loadFromFile("assets/font/angrybirds.ttf")) {
                throw std::runtime_error("Failed to load font");
        }
        GameText::setDefaultFont(&font);
        initText();
        initButtons();
        initStars();
        setBackground("home_bg");
    }

    std::optional<std::string> getClickedButton(const sf::Vector2f& mousePos) {
        for (const auto& [name, button] : buttons) {
            if (button.isClicked(mousePos)) {
                return name;
            }
        }
        return std::nullopt;
    }

    void updateScale(){
        sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());
        sf::Vector2f textureSize = static_cast<sf::Vector2f>(background_sprite.getTexture()->getSize());
        scaleX = windowSize.x / textureSize.x;
        scaleY = windowSize.y / textureSize.y;   

        background_sprite.setScale(scaleX, scaleY);  
        if (isOverlayActive) {
            overlay_sprite.setScale(scaleX, scaleY);
        }
        
        updateAllPositions();
    } 

    void updateAllPositions(){
        for (auto& [name, button] : buttons) {
            button.updatePosition(scaleX, scaleY);
        }  
        for (auto& [name, text] : texts) {
            text.updatePosition(scaleX, scaleY);
        }
        for (Star& star : stars) {
            star.updatePosition(scaleX, scaleY);
        }
   } 

    void updateScore(int score) {
        texts["score"].setString("Score: " + std::to_string(score));
        texts["final_score"].setString(std::to_string(score));
    }

    void drawHome(){
        setBackground("home_bg");
        window.draw(background_sprite);

        activateButtons({"play_btn", "help_btn", "music_btn"});
        buttons["play_btn"].draw(window);
        buttons["help_btn"].draw(window);
        buttons["music_btn"].draw(window);
          
        /*if (buttons.find("play_btn") != buttons.end()) {
            std::cout << "Drawing play button at position: " 
                    << buttons["play_btn"].getPosition().x << ", " 
                    << buttons["play_btn"].getPosition().y << std::endl;
            buttons["play_btn"].draw(window);
        } else {
            std::cout << "Play button not found in buttons map" << std::endl;
        }*/

    }

    void drawHelp(){
        setBackground("help_bg");
        window.draw(background_sprite);
   
        activateButtons({"no_btn"});
        buttons["no_btn"].draw(window);
        texts["help_title"].draw(window);
        texts["help_body"].draw(window);
    }

    void drawLevel(){
        setBackground("level_bg");
        window.draw(background_sprite);

        activateButtons({"home_btn", "lvl1_btn", "lvl2_btn", "lvl3_btn"});
        buttons["home_btn"].draw(window);
        buttons["lvl1_btn"].draw(window);
        buttons["lvl2_btn"].draw(window);
        buttons["lvl3_btn"].draw(window);
        
        texts["level1"].draw(window);
        texts["level2"].draw(window);
        texts["level3"].draw(window);
    }    

    void drawGame(int level){
        currentLevel = level;
        switch (currentLevel) {
            case 1: setBackground("lvl1_bg"); break;
            case 2: setBackground("lvl2_bg"); break;
            case 3: setBackground("lvl3_bg"); break;
        }
        window.draw(background_sprite);

        activateButtons({"back_btn"});
        buttons["back_btn"].draw(window);
        texts["score"].draw(window);
    }

    void drawWin(int starCount){
        switch (currentLevel) {
            case 1: setBackground("lvl1_bg"); break;
            case 2: setBackground("lvl2_bg"); break;
            case 3: setBackground("lvl3_bg"); break;
        }
        setOverlay("win_bg");
        window.draw(background_sprite);
        window.draw(overlay_sprite);
        
        activateButtons({"level_btn", "next_btn"});
        buttons["level_btn"].draw(window);
        buttons["next_btn"].draw(window);
        texts["final_score"].draw(window);

        for (int i = 0; i < starCount; i++) {
            window.draw(stars[i].sprite);
        }
    }

    void drawLost(){
        switch (currentLevel)
        {
        case 1: setBackground("lvl1_bg"); break;
        case 2: setBackground("lvl2_bg"); break;
        case 3: setBackground("lvl3_bg"); break;
        }
        setOverlay("lost_bg");
        window.draw(background_sprite);
        window.draw(overlay_sprite);

        activateButtons({"level_btn", "replay_btn"});
        buttons["level_btn"].draw(window);
        buttons["replay_btn"].draw(window);
    }
    
private:
    sf::RenderWindow& window;
    std::unordered_map<std::string, Button> buttons;
    std::unordered_map<std::string, GameText> texts;
    sf::Font font;
    sf::Sprite background_sprite;
    sf::Sprite overlay_sprite;
    bool isOverlayActive = false;
    float scaleX = 1.f;
    float scaleY = 1.f;
    int currentLevel;

    struct Star {
        sf::Sprite sprite;
        sf::Vector2f defaultPosition;
        Star(const sf::Texture& texture, const sf::Vector2f& position): sprite(texture), defaultPosition(position) {
            sprite.setPosition(position);
        }

        void updatePosition(float scaleX, float scaleY) {
            float newX = defaultPosition.x * scaleX;
            float newY = defaultPosition.y * scaleY;
            sprite.setPosition(newX, newY);
        }
    };
    std::vector<Star> stars;

    void setBackground (const std::string& texture_name) {
        background_sprite.setTexture(TextureManager::getTexture(texture_name));
        updateScale();
    }

    // set overlay for dimming effect  (double layer)
    void setOverlay (const std::string& texture_name) {
        overlay_sprite.setTexture(TextureManager::getTexture(texture_name));
        overlay_sprite.setScale(scaleX, scaleY);
        isOverlayActive = true;
    }

    void activateButtons(const std::vector<std::string>& buttonNames) {
        for (auto& [name, button] : buttons) {
            button.deactivate();
        }

        for (const auto& name : buttonNames) {
            auto it = buttons.find(name);
            if (it != buttons.end()) {
                it->second.activate();
            } 
        }
    }
    
    void initButtons(){ 
        buttons["play_btn"] = Button(TextureManager::getTexture("play_btn"));
        buttons["help_btn"] = Button(TextureManager::getTexture("help_btn"));
        buttons["music_btn"] = Button(TextureManager::getTexture("music_btn"));
        buttons["no_music_btn"] = Button(TextureManager::getTexture("no_music_btn"));
        buttons["no_btn"] = Button(TextureManager::getTexture("no_btn"));
        buttons["home_btn"] = Button(TextureManager::getTexture("home_btn"));
        buttons["lvl1_btn"] = Button(TextureManager::getTexture("lvl1_btn"));
        buttons["lvl2_btn"] = Button(TextureManager::getTexture("lvl2_btn"));
        buttons["lvl3_btn"] = Button(TextureManager::getTexture("lvl3_btn"));
        buttons["back_btn"] = Button(TextureManager::getTexture("back_btn"));
        buttons["level_btn"] = Button(TextureManager::getTexture("level_btn"));
        buttons["replay_btn"] = Button(TextureManager::getTexture("replay_btn"));
        buttons["next_btn"] = Button(TextureManager::getTexture("next_btn"));
        scaleButtons();
        initButtonPosition();
    }

    void scaleButtons() {
        buttons["help_btn"].setScale(sf::Vector2f(112.f,114.f));
        buttons["music_btn"].setScale(sf::Vector2f(112.f,114.f));  
        buttons["no_music_btn"].setScale(sf::Vector2f(112.f,114.f));
        buttons["home_btn"].setScale(sf::Vector2f(112.f,114.f));
        buttons["lvl1_btn"].setScale(sf::Vector2f(336.f,653.f));
        buttons["lvl2_btn"].setScale(sf::Vector2f(336.f,653.f));
        buttons["lvl3_btn"].setScale(sf::Vector2f(336.f,653.f));
        buttons["back_btn"].setScale(sf::Vector2f(112.f,114.f));
        buttons["replay_btn"].setScale(sf::Vector2f(112.f,114.f));
    }
    void initButtonPosition() {
        buttons["play_btn"].setDefaultPosition(730.f, 452.f);  
        buttons["help_btn"].setDefaultPosition(1800.0f, 980.f);     
        buttons["music_btn"].setDefaultPosition(100.f, 980.f);     
        buttons["no_music_btn"].setDefaultPosition(100.f, 980.f);   
        buttons["no_btn"].setDefaultPosition(290.3f, 798.1f);
        buttons["home_btn"].setDefaultPosition(53.6f, 1105.3f);
        buttons["lvl1_btn"].setDefaultPosition(368.6f, 337.f);  
        buttons["lvl2_btn"].setDefaultPosition(829.4f, 96.f); 
        buttons["lvl3_btn"].setDefaultPosition(1300.5f, 348.f);     
        buttons["back_btn"].setDefaultPosition(15.4f, 10.8f);
        buttons["level_btn"].setDefaultPosition(854.6f, 959.6f); 
        buttons["replay_btn"].setDefaultPosition(1017.f, 961.f);
        buttons["next_btn"].setDefaultPosition(1017.f, 961.f); 
   }

    void initText() {
        texts["score"] = GameText(56, sf::Vector2f(1656.2f, 10.4f), "", sf::Color::White, sf::Color::Black);
        texts["final_score"] = GameText(56, sf::Vector2f(1656.2f, 10.4f), "", sf::Color::White, sf::Color::Black);
        texts["help_title"] = GameText(223, sf::Vector2f(795.f, 118.8f), "Help", sf::Color::Black, sf::Color::White);
        texts["help_body"] = GameText(75, sf::Vector2f(632.8f, 472.8f), "Drag the bird and shot!\n          That's it! :D", sf::Color::Black, sf::Color::White);
        texts["level1"] = GameText(117, sf::Vector2f(519.8f, 205.8f), "1", sf::Color::White, sf::Color::Black);
        texts["level2"] = GameText(117, sf::Vector2f(971.8f, 740.8f), "2", sf::Color::White, sf::Color::Black);
        texts["level3"] = GameText(117, sf::Vector2f(1450.8f, 221.8f), "3", sf::Color::White, sf::Color::Black);
    }


    void initStars() {
        stars = {
            Star(TextureManager::getTexture("star1"), sf::Vector2f(616.4f, 345.4f)),
            Star(TextureManager::getTexture("star2"), sf::Vector2f(863.5f, 324.4f)),
            Star(TextureManager::getTexture("star3"), sf::Vector2f(1129.5f, 342.8f))
        };    
    }


};

#endif // GUI_HPP