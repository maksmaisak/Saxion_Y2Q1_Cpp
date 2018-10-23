//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_SYSTEM_H
#define SAXION_Y2Q1_CPP_SYSTEM_H

#include <SFML/Graphics.hpp>

class Engine;

class System {

public:
    explicit System(Engine& engine);
    virtual ~System() = default;

    virtual void update(float dt) {}
    virtual void draw() {}

protected:
    Engine& m_engine;
    class EntityRegistry& m_registry;
};

#endif //SAXION_Y2Q1_CPP_SYSTEM_H
