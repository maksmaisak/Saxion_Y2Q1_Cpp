//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Entity.h"

class Engine {

public:
    static Engine& getInstance();
    Engine();
    void run();
    std::shared_ptr<Entity> makeEntity();

private:

    static Engine _instance;

    sf::RenderWindow _window;
    std::vector<std::shared_ptr<Entity>> _entities;

    Player _player;

    void render();
    void update(float dt);

    void remove(Entity* pEntity);
    friend void Entity::destroy();
};


#endif //SAXION_Y2Q1_CPP_ENGINE_H
