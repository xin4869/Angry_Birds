#include "includes.hpp"


// for debugging
void printInfo(Object* obj)
{
  b2Vec2 position = obj->body->GetPosition();
  float angle = obj->body->GetAngle();
  printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
}


int main(void) {
  /*
  currently makes some objects, simulates and displays one of them
  this is just example code to show how these could be used
  */

  std::cout << "Debug1" << std::endl;

  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);

  /*
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -10.0f);
  
  b2Body* groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);
  
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 4.0f);
  
  b2Body* body = world.CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);
  
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  body->CreateFixture(&fixtureDef);
  */

  // creating Objects. these use defaults. can also give parameters
  NormalBird bird = NormalBird(&world, 3, 5);
  Pig pig = Pig::GetNormalPig(&world, 4, 5);
  Block ice = Block::GetIceBlock(&world, 5, 5, 1, 3);
  Block fixed = Block::GetFixedBlock(&world, 4, 1, 10, 2);
  
  bird.Attack();

  float frameRate = 60.0f;
  float timeStep = 1.0f / frameRate;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  auto window = sf::RenderWindow({1080u, 720u}, "CMake SFML Project");
  window.setPosition(sf::Vector2i(200, 200));
  window.setFramerateLimit(frameRate);
	
  tgui::Gui gui(window);
	MainMenu mainMenu(2);
  LevelUI levelUI(2);
  gui.add(mainMenu.group);
  gui.add(levelUI.group);

  while (window.isOpen()) {
    for (auto event = sf::Event(); window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      gui.handleEvent(event);
    }
    //for (int32 i = 0; i < 60; ++i) {
    world.Step(timeStep, velocityIterations, positionIterations);
    //printInfo(&ice);
    //printInfo(&bird);
    //printInfo(&pig);
    //printInfo(&fixed);
    //}

    // something like this to draw but more organized
    b2Vec2 pos = 75.0 * bird.body->GetPosition();
    bird.sprite.setPosition(pos.x, 800 - pos.y);

    window.clear(sf::Color::White);
    window.draw(bird.sprite);
		gui.draw();
    window.display();
  }

  return 0;
}
