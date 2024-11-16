#ifndef VISUAL_GAME_RENDER_HPP
#define VISUAL_GAME_RENDER_HPP

#include "game.hpp"


class GameRender{
public: 
    GameRender(sf::RenderWindow& game_window): window(game_window) {
    }

    void init(){}
private:
    sf::RenderWindow& window;
};

#endif


