#include "game.hpp"
#include "visual/gui.hpp"


// for debugging
void printInfo(Object* obj)
{
  b2Vec2 position = obj->body->GetPosition();
  float angle = obj->body->GetAngle();
  printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
}


int main(void) {

  const float frameRate = 60.0f;
  //calculate actual varying elapsed time between frames

  //update physics with fixed time step
  const float time_step = 1.0f / frameRate;
  const int max_step = 5;

  auto window = sf::RenderWindow({1080u, 720u}, "Angry Birds");
  window.setFramerateLimit(frameRate);

  Game game(window);
  if (!game.init()) {return 0};

  while (window.isOpen()) {
    //events handling
    for (auto event = sf::Event(); window.pollEvent(event);) {

      // opening/closing game window
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // mouse click event
      if (event.type == sf::Event::MouseButtonPressed) {
        game.mouseClicked(event);
      } else if (event.type == sf::Event::MouseButtonReleased){
        game.mouseReleased(event);
      }

      // window resizing event - update UI positions
      if (event.type == sf::Event::Resized){
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea)); 
      }

    }


    game.update();

    window.clear();

    game.render();

    window.display();
  }

  return 0;
}
