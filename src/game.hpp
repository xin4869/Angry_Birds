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
#include "visual/game_render.hpp"

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
    renderer = std::make_unique<GameRender>(window);
    
    SoundManager::playMusic("Theme song");
  } 

  ~Game() {}

  void run() {
    sf::Clock clock;
    while (window.isOpen()) {
      sf::Time elapsed = clock.restart();
      float deltaTime = elapsed.asSeconds();

      handleEvents();
      update(deltaTime);
      draw();
    }
    window.close();
  }

  void update(float deltaTime){
    if (level) {
      level->update(deltaTime);
      int currentScore = static_cast<int>(level->getScore());
      gui->updateScore(currentScore);
    }
  }

  void draw(){
    window.clear();
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
          gui->drawGame(levelNumber);
          renderer->renderGame(*level);
          //renderer->drawGameObjects(levelNumber);
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
    
      if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        handleMousePress();
      } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        handleMouseRelease();
      } else if (event.type == sf::Event::MouseMoved) {
        handleMouseMove();
      }

      // window resizing event - update UI positions, sizes
      if (event.type == sf::Event::Resized){
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea)); 
        gui->updateScale();
        renderer->init();
      }
    }
  }

  b2Vec2 screenToWorldPos(const sf::Vector2i& screenPos) {
    sf::Vector2f worldPos = window.mapPixelToCoords(screenPos);
    return b2Vec2(worldPos.x / ObjectDefs::pixel_per_meter, worldPos.y / ObjectDefs::pixel_per_meter);
  }

  void handleMousePress() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    auto clicked_button = gui->getClickedButton(mousePos);
    if (clicked_button) {
      handleButtonClicks(*clicked_button);
    } else if (currentState == GameState::in_game && level) {
      //b2Vec2 b2WorldPos = screenToWorldPos(static_cast<sf::Vector2i>(mousePos));
      b2Vec2 b2WorldPos = renderer->toGamePos(static_cast<sf::Vector2i>(mousePos));
      
      Bird* currentBird = level->getCurrentBird();
      // implicitly choose the action
      if (!currentBird || !currentBird->getCanAttack()) {
        level->setNextBird();
      }
      else if (currentBird->getHP() != currentBird->getMaxHP() ||
            currentBird->getBody()->GetLinearVelocity().LengthSquared() > 0) {
        currentBird->Attack();
      }
      else {
      level->startDragging(b2WorldPos);
      }
    }       
  }

  void handleMouseRelease() {
    if (currentState == GameState::in_game && level) {
      level->endDragging();
    }
  }

  void handleMouseMove() {
    if (currentState == GameState::in_game && level) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      //b2Vec2 b2WorldPos = screenToWorldPos(mousePos);
      b2Vec2 b2WorldPos = renderer->toGamePos(mousePos);
      level->updateDragging(b2WorldPos);
    }
  }

  void handleButtonClicks(const std::string& button_name){
    std::cout << "Button clicked: " << button_name << std::endl;
    switch (currentState){
      case GameState::home: 
        if(button_name == "play_btn") {
          std::cout << "Changing state to level" << std::endl;
          currentState = GameState::level;
        } else if (button_name == "help_btn") {
          currentState = GameState::help;
        } else if (button_name == "music_btn" || button_name == "no_music_btn") {
          SoundManager::setMusicVolume(SoundManager::getMusicVolume() ? 0 : 100);
          gui->toggleMusic();
        } break; 
      
      case GameState::help: 
        if (button_name == "no_btn") {
          currentState = GameState::home;
        } break;

      case GameState::level: 
        if (button_name == "home_btn") {
          currentState = GameState::home;
        } else if (
          button_name == "lvl1_btn" || 
          button_name == "lvl2_btn"|| 
          button_name == "lvl3_btn"){
          int level = (button_name == "lvl1_btn") ? 1 : (button_name == "lvl2_btn") ? 2 : 3;
          setLevel(level);
          currentState = GameState::in_game;
          SoundManager::playMusic("Forest ambient");
        } break;

      case GameState::in_game:
        if (button_name == "back_btn") {
          currentState = GameState::level;
          SoundManager::playMusic("Theme song");
        } else if (level->isWin()) {
          currentState = GameState::win;
        } else if (level->isLost()) {
          currentState = GameState::lost;
        }
        break; 
  
      case GameState::win: 
      case GameState::lost:
          if (button_name == "level_btn") {
            currentState = GameState::level;
          } else if (button_name == "next_btn") {
            levelNumber++;
            setLevel(levelNumber);  
            currentState = GameState::in_game;
          } else if (button_name == "replay_btn") {
            setLevel(levelNumber);  
            currentState = GameState::in_game;
          } break;      
    }
  }


  b2World& getWorld() { return level->getWorld(); }

  void setLevel(int level_number){
    if (level_number > MAX_LEVELS || level_number <= 0) {
      std::cerr << "Invalid level number: " << level_number << std::endl;
      return;
    }
    level = std::make_unique<Level>(level_number);
    levelNumber = level_number;

    level->setActive(true);
  }


  
private:
  sf::Music music;
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