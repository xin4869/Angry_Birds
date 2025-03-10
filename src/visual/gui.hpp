#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <unordered_map>
#include <optional>
#include "texture_manager.hpp"
#include "button.hpp"
#include "game_text.hpp"

#ifndef GUI_HPP
#define GUI_HPP


/**
 * @brief GUI class for the game.
 */
class GUI {
public:
    GUI(sf::RenderWindow& game_window): window(game_window) {
        init();
    }

    /**
     * @brief Sets up the GUI
     */
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

    /**
     * @brief Get name of button pos is on
     * @param mousePos 
     * @return std::optional<std::string> name of button
     */
    std::optional<std::string> getClickedButton(const sf::Vector2f& mousePos) {
        for (const auto& [name, button] : buttons) {
            if (button.isClicked(mousePos)) {
                return name;
            }
        }
        return std::nullopt;
    }

    /**
     * @brief Updates the scale of the GUI based on window size
     */
    void updateScale(){
        sf::Vector2f windowSize(window.getSize());
        sf::Vector2f textureSize(background_sprite.getTexture()->getSize());
        scaleX = windowSize.x / textureSize.x;
        scaleY = windowSize.y / textureSize.y;

        ObjectDefs::pixel_per_meter = ObjectDefs::default_pixel_per_meter * std::min(scaleX, scaleY);

        background_sprite.setScale(scaleX, scaleY);  
        overlay_sprite.setScale(scaleX, scaleY);
        
        updateAllPositions();
        updateAllSizes();
    } 

    /**
     * @brief Update positions of all GUI elements
     */
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

    /**
     * @brief Update sizes of all GUI elements
     */
   void updateAllSizes() {
        for (auto& [name, button] : buttons) {
            button.updateSize(scaleX, scaleY);
        }
        for (auto& [name, text] : texts) {
            text.updateSize(scaleX, scaleY);
        }
        for (Star& star : stars) {
            star.updateSize(scaleX, scaleY);
        }
   }

    /**
     * @brief Update score texts
     * @param score 
     */
    void updateScore(int score) {
        texts["score"].setString("Score: " + std::to_string(score));
        texts["final_score"].setString(std::to_string(score));
    }

    /**
     * @brief Update birds left text
     * @param count 
     */
    void updateBirdsLeft(int count) {
        texts["birds_left"].setString("Birds Left: " + std::to_string(count));
    }

    void toggleMusic() {
        isMusicOn = !isMusicOn;
    }

    /**
     * @brief Draws the home screen.
     */
    void drawHome(){
        setBackground("home_bg");
        window.draw(background_sprite);

        activateButtons({"play_btn", "help_btn", "music_btn"}); //activate music or no music btn
        buttons["play_btn"].draw(window);
        buttons["help_btn"].draw(window);
        buttons["music_btn"].draw(window); //button.draw will only draw active btn
        buttons["no_music_btn"].draw(window); 

    }

    /**
     * @brief Draw help screen
     */
    void drawHelp(){
        setBackground("help_bg");
        window.draw(background_sprite);
   
        activateButtons({"no_btn"});
        buttons["no_btn"].draw(window);
        texts["help_title"].draw(window);
        texts["help_body"].draw(window);
    }

    /**
     * @brief Draw level screen
     */
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

    /**
     * @brief Draws the ingame screen
     * @param level level number
     */
    void drawGame(int level){
        currentLevel = level;
        switch (currentLevel) {
            case 1: setBackground("level1_bg"); break;
            case 2: setBackground("level2_bg"); break;
            case 3: setBackground("level3_bg"); break;
        }
        window.draw(background_sprite);

        activateButtons({"back_btn"});
        buttons["back_btn"].draw(window);
        texts["score"].draw(window);
        texts["birds_left"].draw(window);
    }

    /**
     * @brief Draw win screen
     * @param starCount amount of stars
     */
    void drawWin(int starCount){
        switch (currentLevel) {
            case 1: setBackground("level1_bg"); break;
            case 2: setBackground("level2_bg"); break;
            case 3: setBackground("level3_bg"); break;
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

    /**
     * @brief Draw lose screen
     */
    void drawLost(){
        switch (currentLevel)
        {
        case 1: setBackground("level1_bg"); break;
        case 2: setBackground("level2_bg"); break;
        case 3: setBackground("level3_bg"); break;
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
    bool isMusicOn = true;
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

        void updateSize (float scaleX, float scaleY) {
            sprite.setScale(scaleX, scaleY);
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
    }

    void activateButtons(const std::vector<std::string>& buttonNames) {
        for (auto& [name, button] : buttons) {
            button.deactivate();
        }
        for (const auto& name : buttonNames) {
            if (name == "music_btn" || name == "no_music_btn") {
                buttons[isMusicOn? "music_btn" : "no_music_btn"].activate();
            } else {
                auto it = buttons.find(name);
                if (it != buttons.end()) {
                    it->second.activate();
                } 
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
        initButtonPosition();
    }

    void initButtonPosition() {
        buttons["play_btn"].setDefaultPosition(730.f, 472.f);  
        buttons["help_btn"].setDefaultPosition(1800.0f, 990.f);     
        buttons["music_btn"].setDefaultPosition(100.f, 987.f);     
        buttons["no_music_btn"].setDefaultPosition(100.f, 987.f);   
        buttons["no_btn"].setDefaultPosition(290.3f, 798.1f);
        buttons["home_btn"].setDefaultPosition(53.6f, 1105.3f);
        buttons["lvl1_btn"].setDefaultPosition(368.6f, 317.f);  
        buttons["lvl2_btn"].setDefaultPosition(829.4f, 317.f); 
        buttons["lvl3_btn"].setDefaultPosition(1300.5f, 317.f);     
        buttons["back_btn"].setDefaultPosition(15.4f, 10.8f);
        buttons["level_btn"].setDefaultPosition(854.6f, 959.6f); 
        buttons["replay_btn"].setDefaultPosition(1017.f, 961.f);
        buttons["next_btn"].setDefaultPosition(1017.f, 961.f); 
   }

    void initText() {
        texts["score"] = GameText(56, sf::Vector2f(1686.2f, 10.4f), "");
        texts["final_score"] = GameText(80, sf::Vector2f(903.0f, 700.0f), "");
        texts["birds_left"] = GameText(56, sf::Vector2f(1286.2f, 10.4f), "");
        texts["help_title"] = GameText(203, sf::Vector2f(795.f, 128.8f), "Help", sf::Color::Black, sf::Color::White);
        texts["help_body"] = GameText(75, sf::Vector2f(632.8f, 472.8f), "Drag the bird and shot!\n          That's it! :D", sf::Color::Black, sf::Color::White);
        texts["level1"] = GameText(117, sf::Vector2f(505.8f, 195.8f), "1");
        texts["level2"] = GameText(117, sf::Vector2f(971.8f, 195.8f), "2");
        texts["level3"] = GameText(117, sf::Vector2f(1450.8f, 195.8f), "3");
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