#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "objects/special_birds.hpp"
#include "objects/pig.hpp"
#include "objects/block.hpp"
#include "visual/gui.hpp"
#include "visual/game_render.hpp"


enum GameState {
    menu = 0,
    in_game = 1,
    win = 2,
    lost = 3
  };

class Game {
public:
  Game(sf::RenderWindow& game_window)
    :gui(game_window),
    renderer(game_window),
    gravity(0.0f, -10.0f),
    world(gravity)  {
    game_state = menu;
  }
  ~Game() {}
  
  bool init(){
    return gui.init() && renderer.init()
  }
  void update();
  void render();

  void loadLevel(int levelNumber){}
  void launch(){}
   

  
  // creating Objects. these use defaults. can also give parameters
  NormalBird bird = NormalBird(&world, 3, 5);
  Pig pig = Pig::GetNormalPig(&world, 4, 5);
  Block ice = Block::GetIceBlock(&world, 5, 5, 1, 3);
  Block fixed = Block::GetFixedBlock(&world, 4, 1, 10, 2);
  
  bird.Attack();

  int32 velocityIterations = 6;
  int32 positionIterations = 2;


  world.Step(timeStep, velocityIterations, positionIterations);
  printInfo(&bird);
  b2Vec2 pos = 75.0 * bird.body->GetPosition();
  bird.sprite.setPosition(pos.x, 800 - pos.y);



    // game render
 
    // game objects drawing  
  window.draw(bird.sprite, sf::RenderStates(sf::BlendAlpha));

    
  
private:
  
  GameState game_state;

  GUI gui;
  GameRender renderer;

  b2Vec2 gravity;
  b2World world;






};


#endif