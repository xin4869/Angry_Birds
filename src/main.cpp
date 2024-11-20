#include "game.hpp"
#include "visual/gui.hpp"


int main(void) {
  auto window = sf::RenderWindow({1080u, 720u}, "Angry Birds");

  Game game(window);
  if (!game.init()) {return 0;}
  window.setFramerateLimit(game.getFrameRate());

  NormalBird bird(game.getWorld(), 0, 0);
  Pig pig(game.getWorld(), 0, 0, &ObjectDefs::normalPigDefaults);
  Block block(game.getWorld(), 0, 0, &ObjectDefs::iceRectL);

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

}

