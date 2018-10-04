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
    Engine();

    static Engine& getInstance();
    void run();

    // This has to be defined in the header file to make sure all needed specializations are made during compilation and before linking
    template<class T = Entity>
    std::shared_ptr<T> makeEntity() {

        static_assert(std::is_base_of<Entity, T>::value, "T in makeEntity<T> must derive from Entity");

        std::shared_ptr<T> pEntity = std::make_shared<T>();
        _entities.push_back(pEntity);
        return pEntity;
    }

private:

    static Engine _instance;

    sf::RenderWindow _window;
    std::vector<std::shared_ptr<Entity>> _entities;

    void render();
    void update(float dt);

    void remove(Entity* pEntity);
    friend void Entity::destroy();
};

#endif //SAXION_Y2Q1_CPP_ENGINE_H
