//
// Created by Maksym Maisak on 17/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COMPONENT_H
#define SAXION_Y2Q1_CPP_COMPONENT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntityRegistry.h"

class Actor;

class Behavior {

public:
    explicit Behavior(Actor& actor);
    virtual ~Behavior() = default;

    inline Actor& getActor() const {return m_actor;}

    virtual void update(float dt) {};
    virtual void draw(sf::RenderTarget& renderTarget) {};

protected:
    Actor& m_actor;
    Engine& m_engine;
    EntityRegistry& m_registry;
};

#endif //SAXION_Y2Q1_CPP_COMPONENT_H
