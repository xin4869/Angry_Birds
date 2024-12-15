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


/**
 * @brief Game class for the game.
 */
class Game {
public:
  Game() {
    window.create(sf::VideoMode(defaultWindowWidth, defaultWindowHeight), "Angry Birds");
    sf::Image icon;
    icon.loadFromFile("assets/textures/normal_bird/normal/1.png");
    window.setIcon(80, 76, icon.getPixelsPtr());
    centerWindow();
    window.setFramerateLimit(frameRate);

    TextureManager::loadAllTextures();
    SoundManager::loadAllSounds();

    gui = std::make_unique<GUI>(window);
    renderer = std::make_unique<GameRender>(window);
    
    SoundManager::playMusic("Theme song");
  } 

  ~Game() {
    SoundManager::releaseResources();
  }

  /**
   * @brief Runs the game
   */
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

  /**
   * @brief Updates the game
   * @param deltaTime update by this time (s)
   */
  void update(float deltaTime){
    if (level) {
      if (level->getCurrentBird() && level->getCurrentBird()->isUsed()) {
        renderer->setCenter(std::max(0.0f, level->getCurrentBird()->getBody()->GetPosition().x + 5.0f), renderer->getCenter().y);
      } else if (level) {
        renderer->setCenter(std::max(0.0f, renderer->getCenter().x - level->getTimestep() * 30.0f), renderer->getCenter().y);
      }
      level->update(deltaTime);
      int currentScore = static_cast<int>(level->getScore());
      gui->updateScore(currentScore);
      gui->updateBirdsLeft(level->getUnusedBirds().size());
      if (currentState == GameState::in_game && level->isWin()) {
        currentState = GameState::win;
      } else if (currentState == GameState::in_game && level->isLost()) {
        currentState = GameState::lost;
      }
    }
  }

  /**
   * @brief Draws game and gui
   */
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

  /**
   * @brief Handles sfml events
   */
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
        renderer->setBounds();
      }
    }
  }

  /**
   * @brief Handles mouse presses, performs actions based on it
   */

  void handleMousePress() {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
    auto clicked_button = gui->getClickedButton(mousePos);
    if (clicked_button) {
      handleButtonClicks(*clicked_button);
    } else if (currentState == GameState::in_game && level) {
        if (level->isWin()) {
          currentState = GameState::win;
          return;
        } else if (level->isLost()) {
          currentState = GameState::lost;
          return;
        }
      
      b2Vec2 b2WorldPos = renderer->toGamePos(mousePos);
      
      Bird* currentBird = level->getCurrentBird();
 
      if (currentBird) {
        if (currentBird->isMoving()) {
          currentBird->Attack();
        } else if (!currentBird->isUsed()) {
          level->startDragging(b2WorldPos);
        }
      }
    }
  }

  /**
   * @brief Handles mouse releases and performs relevant actions
   */
  void handleMouseRelease() {
    if (currentState == GameState::in_game && level) {
      level->endDragging();
    }
  }

  /**
   * @brief Handles mouse movement and performs relevant actions
   */
  void handleMouseMove() {
    if (currentState == GameState::in_game && level) {
      sf::Vector2f mousePos(sf::Mouse::getPosition(window));
      b2Vec2 b2WorldPos = renderer->toGamePos(mousePos);
      level->updateDragging(b2WorldPos);
    }
  }

  /**
   * @brief Handles button clicks, clicks the button and performs it's action
   * @param button_name Name of button clicked (see gui)
   */
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
          int levelNum = (button_name == "lvl1_btn") ? 1 : (button_name == "lvl2_btn") ? 2 : 3;
          setLevel(levelNum);
          currentState = GameState::in_game;
          SoundManager::playMusic("Forest ambient");
        } break;

      case GameState::in_game:
        if (button_name == "back_btn") {
          currentState = GameState::level;
          SoundManager::playMusic("Theme song");
        }
        break; 
  
      case GameState::win: 
      case GameState::lost:
          if (button_name == "level_btn") {
            currentState = GameState::level;
            SoundManager::playMusic("Theme song");
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

  /**
   * @brief Sets and loads a level
   * @param level_number level to load
   */
  void setLevel(int level_number){
    if (level_number > MAX_LEVELS || level_number <= 0) {
      std::cerr << "Invalid level number: " << level_number << std::endl;
      return;
    }
    level = std::make_unique<Level>(level_number);
    levelNumber = level_number;
    renderer->setBounds();

    level->setActive(true);
  }

  /**
   * @brief Resizes and centers the window
   */
  void centerWindow() {
    int desktop_width = sf::VideoMode::getDesktopMode().width;
    int desktop_height = sf::VideoMode::getDesktopMode().height;

    float scaleFactorW = desktop_width * 0.9f / (window.getSize().x);
    float scaleFactorH = desktop_height * 0.9f / (window.getSize().y);
    float scaleFactor = std::min(scaleFactorW, scaleFactorH);
    window.setSize(sf::Vector2u(window.getSize().x * scaleFactor, window.getSize().y * scaleFactor));

    int windowPosX = std::max(0.f, (desktop_width - window.getSize().x) / 2.f);
    int windowPosY = std::max(0.f, (desktop_height - window.getSize().y) / 2.f);
    window.setPosition(sf::Vector2i(windowPosX ,windowPosY));
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

  size_t defaultWindowWidth = 2000;
  size_t defaultWindowHeight = 1250;

  const float frameRate = 60.0f;
};


#endif