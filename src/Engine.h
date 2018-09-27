//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Engine {

public:
    static Engine getInstance();
    Engine();
    void run();

private:

    static Engine _instance;

    sf::RenderWindow _window;

    Player _player;

    void render();
    void update(float dt);
};


#endif //SAXION_Y2Q1_CPP_ENGINE_H
