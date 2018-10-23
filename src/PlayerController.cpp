//
// Created by Maksym Maisak on 27/9/18.
//

#include <iostream>
#include <cmath>
#include "PlayerController.h"
#include "Input.h"
#include "MyMath.h"

PlayerController::PlayerController(Actor& actor) : Behavior(actor) {

    std::cout << "PlayerController()" << std::endl;
    m_registry.get<en::Transformable>(actor).setRotation(-90.f);
}

bool shouldAccelerate();
sf::Vector2f getDirection(float angle);

void PlayerController::update(float dt) {

    auto& tf = m_registry.get<en::Transformable>(m_actor);

    float currentRotation = tf.getRotation();
    {
        float input = en::getAxisHorizontal();
        if (!en::isZero(input)) {
            currentRotation += input * m_rotationSpeed * dt;
            tf.setRotation(currentRotation);
        }
    }

    bool accelerating = shouldAccelerate();
    if (accelerating) {
        m_velocity += getDirection(currentRotation) * m_acceleration * dt;
    } else if (!en::isZero(m_velocity)) {
        m_velocity -= en::normalized(m_velocity) * std::min(m_drag * dt, en::magnitude(m_velocity));
    }

    if (en::magnitude(m_velocity) > m_maxSpeed) {
        en::normalize(m_velocity) *= m_maxSpeed;
    }

    tf.move(m_velocity * dt);

//    if (m_pEngineExhaustParticles) {
//        m_pEngineExhaustParticles->setIsEmissionActive(accelerating);
//    }
}

//void PlayerController::setEngineExhaustParticles(std::shared_ptr<ParticleSystem> pEngineExhaustParticles) {
//    m_pEngineExhaustParticles = std::move(pEngineExhaustParticles);
//}

inline bool shouldAccelerate() {

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

inline sf::Vector2f getDirection(float angle) {

    return {
        std::cos(angle * en::DEG2RAD),
        std::sin(angle * en::DEG2RAD)
    };
}