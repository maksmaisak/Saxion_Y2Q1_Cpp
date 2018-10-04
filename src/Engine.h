//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Entity.h"
#include "Update.h"

class Draw;

class Engine {

public:
    Engine();

    static Engine& getInstance();
    void run();

    template<class T = Entity>
    std::shared_ptr<T> makeEntity();

private:

    static Engine _instance;

    sf::RenderWindow _window;
    std::vector<std::shared_ptr<Entity>> _entities;
    std::vector<std::shared_ptr<Entity>> _update;

    void render();
    void update(float dt);

    void remove(Entity* pEntity);
    friend void Entity::destroy();
};

template<class Derived, class Base>
inline constexpr bool inherits = std::is_base_of<Base, Derived>::value;

// This has to be defined in the header file to make sure all needed
// specializations are made during compilation and before linking.
template<class T>
std::shared_ptr<T> Engine::makeEntity() {

    static_assert(inherits<T, Entity>, "type must derive from Entity");

    std::shared_ptr<T> pEntity = std::make_shared<T>();

    if (inherits<T, Update>) _update.push_back(pEntity);

    _entities.push_back(pEntity);
    return pEntity;
}


#endif //SAXION_Y2Q1_CPP_ENGINE_H
