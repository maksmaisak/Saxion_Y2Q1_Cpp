//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <typeindex>
#include <iostream>
#include "EntityRegistry.h"
#include "Entity.h"
#include "Behavior.h"

template<typename... TComponent>
class EntitiesView;

class Engine {

public:
    Engine(unsigned int width, unsigned int height);
    virtual ~Engine() = default;

    static Engine& getInstance();
    void run();

    inline EntityRegistry& getRegistry() {return m_registry;}
    inline sf::RenderWindow& getWindow() {return m_window;}

    /// Returns the shared_ptr to the child to allow call chaining.
    std::shared_ptr<Entity>& addChild(std::shared_ptr<Entity>& pParent, std::shared_ptr<Entity>& pChild);
    void removeChild(std::shared_ptr<Entity>& pParent, std::shared_ptr<Entity>& pChild);

private:

    static Engine* m_instance;

    EntityRegistry m_registry;
    sf::RenderWindow m_window;
    std::vector<std::shared_ptr<Behavior>> m_components;

    void render();
    void update(float dt);
};

#endif //SAXION_Y2Q1_CPP_ENGINE_H
