//
// Created by Maksym Maisak on 17/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RIGIDBODY_H
#define SAXION_Y2Q1_CPP_RIGIDBODY_H

#include <SFML/Graphics.hpp>
#include "EngineCallbacks.h"
#include "Component.h"

class Rigidbody : public Component, public Update {

    using Component::Component;
public:
    void update(float dt) final;

private:
    sf::Vector2f m_velocity;
    float m_invMass = 1.f;
};


#endif //SAXION_Y2Q1_CPP_RIGIDBODY_H
