//
// Created by Maksym Maisak on 17/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COMPONENT_H
#define SAXION_Y2Q1_CPP_COMPONENT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Engine;
class Entity;

class Component {

public:
    explicit Component(Entity* pEntity) : m_Entity(*pEntity), m_Engine(*(pEntity->getEngine())) {}
    virtual ~Component() = default;

    inline Entity& getEntity() const {return m_Entity;}
    inline Engine& getEngine() const {return m_Engine;}

    virtual void update(float dt) {};
    virtual void draw(sf::RenderTarget& renderTarget) {};

protected:
    Entity& m_Entity;
    Engine& m_Engine;
};

#endif //SAXION_Y2Q1_CPP_COMPONENT_H
