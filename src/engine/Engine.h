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

    /// Returns the shared_ptr to the child to allow call chaining.
    template<class TParent = Entity, class TChild = Entity>
    std::shared_ptr<TChild>& addChild(std::shared_ptr<TParent>& pParent, std::shared_ptr<TChild>& pChild);

    template<class TParent = Entity, class TChild = Entity>
    void removeChild(std::shared_ptr<TParent>& pParent, std::shared_ptr<TChild>& pChild);

    void destroy(Entity& entity);

    sf::RenderWindow& getWindow();

private:

    static Engine* m_instance;

    sf::RenderWindow m_window;
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<Entity>> m_update;
    std::vector<std::shared_ptr<Entity>> m_draw;

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

    if (inherits<T, Update>) m_update.push_back(pEntity);
    if (inherits<T, Draw>  ) m_draw  .push_back(pEntity);

    m_entities.push_back(pEntity);
    return pEntity;
}

template<class TParent, class TChild>
std::shared_ptr<TChild>& Engine::addChild(std::shared_ptr<TParent>& pParent, std::shared_ptr<TChild>& pChild) {

    pParent->addChild(pChild);
    pChild->setParent(pParent);
    return pChild;
}

template<class TParent, class TChild>
void Engine::removeChild(std::shared_ptr<TParent>& pParent, std::shared_ptr<TChild>& pChild) {

    pParent->removeChild(pChild);
    pChild->removeParent();
}
#endif //SAXION_Y2Q1_CPP_ENGINE_H
