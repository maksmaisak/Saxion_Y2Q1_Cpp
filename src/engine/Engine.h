//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <optional>
#include <typeindex>
#include <iostream>
#include "EntityRegistry.h"
#include "Entity.h"
#include "System.h"
#include "Actor.h"

template<typename... TComponent>
class EntitiesView;

class Engine final {

public:
    Engine(unsigned int width, unsigned int height);

    void run();

    inline EntityRegistry& getRegistry() {return m_registry;}
    inline sf::RenderWindow& getWindow() {return m_window;}
    static Engine& getInstance();

    template<typename TSystem, typename... Args>
    TSystem& addSystem(Engine& engine, Args&&... args);

    /// A convenience function which lets you omit passing Engine& to the constructor
    template<typename TSystem, typename... Args>
    TSystem& addSystem(Args&&... args);

    Actor& makeActor();

    void setParent(Entity child, std::optional<Entity> newParent);

private:

    static Engine* m_instance;

    EntityRegistry m_registry;
    sf::RenderWindow m_window;

    std::vector<std::unique_ptr<System>> m_systems;
    std::vector<std::unique_ptr<Actor>>  m_actors;

    void draw();
    void update(float dt);
};

template<typename TSystem, typename... Args>
TSystem& Engine::addSystem(Engine& engine, Args&& ... args) {

    assert(&engine == this);

    std::unique_ptr<TSystem> ptr = std::make_unique<TSystem>(engine, std::forward<Args>(args)...);
    TSystem& system = *ptr;
    m_systems.push_back(std::move(ptr));
    return system;
}

template<typename TSystem, typename... Args>
TSystem& Engine::addSystem(Args&&... args) {
    return addSystem<TSystem>(*this, std::forward(args)...);
}

#endif //SAXION_Y2Q1_CPP_ENGINE_H
