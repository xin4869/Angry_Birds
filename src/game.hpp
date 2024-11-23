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


enum GameState {
    home = 0,
    help = 1,
    levels = 2,
    in_game = 3,
    win = 4,
    lost = 5
  };

class Game {
public:
  Game(sf::RenderWindow& game_window):
    gui(game_window),renderer(game_window) {
      game_state = home;
      TextureManager::loadAllTextures();
      SoundManager::loadAllSounds();
  } 

  ~Game() {}
  
  bool init(){ return 1; }
  void update(){
    // Update physics world
    level.update();
    // Update game objects' positions based on physics simulation
  }
  void render(){}
  void launch(){}

  int getFrameRate() { return frameRate; }

  void mouseClicked(sf::Event event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      float mouse_x = event.mouseButton.x;
      float mouse_y = event.mouseButton.y;


      



    }
  }
  
  void mouseReleased(sf::Event event) {}

  b2World& getWorld() { return level.getWorld(); }

  
private:
  GameState game_state;

  GUI gui;
  GameRender renderer;

  Level level;

  const float frameRate = 60.0f;
  const float timeStep = 1.0f / frameRate;
  //const int max_step = 5;

  int32 velocityIterations = 6;
  int32 positionIterations = 2;





};


#endif