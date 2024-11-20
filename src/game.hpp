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
    gui(game_window),renderer(game_window),gravity(0.0f, -10.0f),world(gravity) {
      game_state = home;
      TextureManager::loadAllTextures();
  } 

  ~Game() {}
  
  bool init(){ return 1; }
  void update(){
    // Update physics world
    world.Step(timeStep, velocityIterations, positionIterations);
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

  b2World* getWorld() { return &world; }

  
private:
  GameState game_state;

  GUI gui;
  GameRender renderer;

  b2Vec2 gravity;
  b2World world;

  std::vector<Bird*>birds;
  std::vector<Pig*>pigs;
  std::vector<Block*> blocks;

  const float frameRate = 60.0f;
  const float timeStep = 1.0f / frameRate;
  //const int max_step = 5;

  int32 velocityIterations = 6;
  int32 positionIterations = 2;
  
  
  void loadLevel(int level){
    std::string path = "levels/level" + std::to_string(level) + ".lvl";
    std::ifstream file(path);

    if(!file.is_open()) {
      std::cerr << "Failed to open level file." << std::endl;
      return;
    }

    birds.clear();
    pigs.clear();
    blocks.clear();

  //TO DO: load data to birds, pigs, blocks
  }





};


#endif