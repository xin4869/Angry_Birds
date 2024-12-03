#ifndef VISUAL_GAME_RENDER_HPP
#define VISUAL_GAME_RENDER_HPP

#include <fstream>
#include <vector>



class GameRender{
public: 
    GameRender(sf::RenderWindow& game_window): window(game_window) {
    }

    void init(){}

    // void renderGame(const Level& level){
    //     drawObjects();
    //     drawBirds();
    //     drawSlingshot();
    //     drawTrajectory();
    // }
   
private:
    sf::RenderWindow& window;
    

    void drawObjects(){}
    void drawBirds(){}

};

#endif


