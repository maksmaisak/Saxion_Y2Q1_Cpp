//
// Created by Maksym Maisak on 27/9/18.
//

#include <iostream>
#include <cmath>
#include "PlayerController.h"
#include "Input.h"
#include "MyMath.h"

PlayerController::PlayerController(Entity* pEntity) : Component(pEntity) {

    std::cout << "PlayerController()" << std::endl;
    m_Entity.setRotation(-90.f);
}

bool shouldAccelerate();
sf::Vector2f getDirection(float angle);

void PlayerController::update(float dt) {

    float currentRotation = m_Entity.getRotation();
    {
        float input = en::getAxisHorizontal();
        if (!en::isZero(input)) {
            currentRotation += input * m_rotationSpeed * dt;
            m_Entity.setRotation(currentRotation);
        }
    }

    bool accelerating = shouldAccelerate();
    if (accelerating) {
        m_velocity += getDirection(currentRotation) * m_acceleration * dt;
    } else if(!en::isZero(m_velocity)) {
        m_velocity -= en::normalized(m_velocity) * std::min(m_drag * dt, en::magnitude(m_velocity));
    }

    if (en::magnitude(m_velocity) > m_maxSpeed) {
        en::normalize(m_velocity) *= m_maxSpeed;
    }

    m_Entity.move(m_velocity * dt);
    {
        sf::Vector2f viewSize = m_Engine.getWindow().getView().getSize();
        sf::Vector2f position = m_Entity.getPosition();
        while (position.x < 0) position.x += viewSize.x;
        while (position.y < 0) position.y += viewSize.y;
        while (position.x > viewSize.x) position.x -= viewSize.x;
        while (position.y > viewSize.y) position.y -= viewSize.y;
        m_Entity.setPosition(position);
    }

    if (m_pEngineExhaustParticles) {
        m_pEngineExhaustParticles->setIsEmissionActive(accelerating);
    }
}

void PlayerController::setEngineExhaustParticles(std::shared_ptr<ParticleSystem> pEngineExhaustParticles) {
    m_pEngineExhaustParticles = std::move(pEngineExhaustParticles);
}

inline bool shouldAccelerate() {

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

inline sf::Vector2f getDirection(float angle) {

    return {
        std::cos(angle * en::DEG2RAD),
        std::sin(angle * en::DEG2RAD)
    };
}