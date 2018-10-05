//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Entity.h"
#include "EngineCallbacks.h"

class Engine {

public:
    Engine(unsigned int width, unsigned int height);

    static Engine& getInstance();
    void run();

    template<class T = Entity, typename... Args>
    std::shared_ptr<T> makeEntity(Args&&... args);

    void destroy(Entity* entity);

    sf::RenderWindow& getWindow();

private:

    static Engine* _instance;

    sf::RenderWindow _window;
    std::vector<std::shared_ptr<Entity>> _entities;
    std::vector<std::shared_ptr<Entity>> _update;
    std::vector<std::shared_ptr<Entity>> _draw;

    void render();
    void update(float dt);
};

template<class Derived, class Base>
inline constexpr bool inherits = std::is_base_of<Base, Derived>::value;

// This has to be defined in the header file to make sure all needed
// specializations are made during compilation and before linking.
template<class T, typename... Args>
std::shared_ptr<T> Engine::makeEntity(Args&&... args) {

    static_assert(inherits<T, Entity>, "type must derive from Entity");

    std::shared_ptr<T> pEntity = std::make_shared<T>(std::forward<Args>(args)...);

    if (inherits<T, Update>) _update.push_back(pEntity);
    if (inherits<T, Draw>  ) _draw  .push_back(pEntity);

    _entities.push_back(pEntity);
    return pEntity;
}

#endif //SAXION_Y2Q1_CPP_ENGINE_H
