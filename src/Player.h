//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_PLAYER_H
#define SAXION_Y2Q1_CPP_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EngineCallbacks.h"

class Player : public Entity, public Update {

public:
    Player();
    void update(float dt);

private:
    float m_acceleration  = 800.f;
    float m_drag          = 50.f;
    float m_rotationSpeed = 360.f;
    sf::Vector2f m_velocity = {0, 0};
};

#endif //SAXION_Y2Q1_CPP_PLAYER_H
