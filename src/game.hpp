#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>

#include "objects/special_birds.hpp"
#include "objects/pig.hpp"
#include "objects/block.hpp"
#include "visual/gui.hpp"
#include "visual/game_render.hpp"
#include "visual/texture_manager.hpp"
#include "sound_manager.hpp"
#include "level.hpp"

enum class GameState {
  home,
  help,
  level,
  in_game,
  win,
  lost
};


class Game {
public:
  Game() {
    window.create(sf::VideoMode(2000, 1250), "Angry Birds");
    window.setFramerateLimit(frameRate);

    TextureManager::loadAllTextures();
    SoundManager::loadAllSounds();

    gui = std::make_unique<GUI>(window);
    gui->init();

    renderer = std::make_unique<GameRender>(window);
  } 

  ~Game() {}

  void run() {
    sf::Clock clock;
    while (window.isOpen()) {
      sf::Time elapsed = clock.restart();
      float deltaTime = elapsed.asSeconds();

      handleEvents();
      update(deltaTime);
      render();
    }
  }
  
  void setLevel(int level_number){
    if (level_number > MAX_LEVELS) {
      std::cerr << "Invalid level number: " << level_number << std::endl;
      return;
    }
    level = std::make_unique<Level>(level_number);
    levelNumber = level_number;
  }

  void update(float deltaTime){
    if (level) {
      level->update(deltaTime);
    }
  }

  void render(){
    window.clear();
    //renderer->drawObjects();
    //renderer->drawBirds();
    if (gui) {
      switch (currentState){
        case GameState::home:
          gui->drawHome();
          break;
        case GameState::help:
          gui->drawHelp();
          break;
        case GameState::level:
          gui->drawLevel();
          break;
        case GameState::in_game:
          renderer->drawGameObjects(levelNumber);
          break;
        case GameState::win:
          gui->drawWin(level->getStars());
          break;
        case GameState::lost:
          gui->drawLost();
          break;
      }
    }
    window.display();
  }

  void handleEvents(){
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mousePos(sf::Mouse::getPosition(window));  // Get mouse position as sf::Vector2f
          auto clicked_button = gui->getClickedButton(mousePos);
          if (clicked_button) {
            handleButtonClicks(*clicked_button);
          }          
        }
      }

      //TODO mouse release

      // window resizing event - update UI positions
      if (event.type == sf::Event::Resized){
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea)); 
        gui->updateScale();
      }

    }
  }
    //TODO music button -> off, on music implementation
  void handleButtonClicks(const std::string& button_name){
    std::cout << "Button clicked: " << button_name << std::endl;
    switch (currentState){
      case GameState::home: 
        if(button_name == "play_btn") {
          std::cout << "Changing state to level" << std::endl;
          currentState = GameState::level;
        } else if (button_name == "help_btn") {
          currentState = GameState::help;
        } break; 
      
      case GameState::help: 
        if (button_name == "no_btn") {
          currentState = GameState::home;
        } break;

      case GameState::level: 
        if (button_name == "home_btn") {
          currentState = GameState::home;
        } else if (button_name == "lv1_btn") {
          setLevel(1);
          currentState = GameState::in_game;        
        } else if (button_name == "lv2_btn") {
          setLevel(2); 
          currentState = GameState::in_game;
        } else if (button_name == "lv3_btn") {
          setLevel(3);
          currentState = GameState::in_game;
        } break;

      case GameState::in_game:
        if (button_name == "back_btn") {
          currentState = GameState::level;
        } break; 
  
      case GameState::win: 
      case GameState::lost:
        if (button_name == "level_btn") {
          currentState = GameState::level;
        } else if (button_name == "next_btn") {
          levelNumber++;
          setLevel(levelNumber);  //TODO game render
          currentState = GameState::in_game;
        } else if (button_name == "replay_btn") {
          setLevel(levelNumber);  //TODO game render
          currentState = GameState::in_game;
        } break;
    }
  }


  b2World& getWorld() { return level->getWorld(); }
  
private:
  sf::RenderWindow window;
  std::unique_ptr<GUI> gui;
  std::unique_ptr<GameRender> renderer;
  std::unique_ptr<Level> level;
  GameState currentState = GameState::home;
  int levelNumber;
  const int MAX_LEVELS = 3;

  const float frameRate = 60.0f;
};


#endif