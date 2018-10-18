//
// Created by Maksym Maisak on 17/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COMPONENT_H
#define SAXION_Y2Q1_CPP_COMPONENT_H

#include <memory>
#include <SFML/Graphics.hpp>

class Engine;
class Entity;

class Component {

public:
    explicit Component(Entity* pEntity) : m_pEntity(pEntity) {}
    virtual ~Component() = default;
    Entity* getEntity() const;
    virtual void update(float dt) {};
    virtual void draw(sf::RenderTarget& renderTarget) {};

private:
    Entity* m_pEntity;
    friend class Entity;
};

#endif //SAXION_Y2Q1_CPP_COMPONENT_H
