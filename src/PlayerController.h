//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_PLAYER_H
#define SAXION_Y2Q1_CPP_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "EngineCallbacks.h"
#include "ParticleSystem.h"

class PlayerController : public Component, public Update {

public:
    explicit PlayerController(Entity* pEntity);
    void update(float dt) final;

    void setEngineExhaustParticles(std::shared_ptr<ParticleSystem> pEngineExhaustParticles);

private:
    float m_acceleration  = 800.f;
    float m_drag          = 50.f;
    float m_rotationSpeed = 360.f;
    sf::Vector2f m_velocity = {0, 0};
    std::shared_ptr<ParticleSystem> m_pEngineExhaustParticles;
};

#endif //SAXION_Y2Q1_CPP_PLAYER_H
