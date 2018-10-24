//
// Created by Maksym Maisak on 24/10/18.
//

#include "Rigidbody.h"
#include "PlayerControlsSystem.h"
#include "Entity.h"
#include "Player.h"
#include "Engine.h"
#include "MyMath.h"
#include "Input.h"

inline bool shouldAccelerate() {

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

inline sf::Vector2f getDirection(float angle) {

    return {
        std::cos(angle * en::DEG2RAD),
        std::sin(angle * en::DEG2RAD)
    };
}

void PlayerControlsSystem::update(float dt) {

    bool accelerate = shouldAccelerate();

    for (Entity e : m_registry.with<Player, en::Transformable, Rigidbody>()) {

        auto& player = m_registry.get<Player>(e);
        auto& tf = m_registry.get<en::Transformable>(e);
        auto& rb = m_registry.get<Rigidbody>(e);

        {
            float currentRotation = tf.getRotation();
            float input = en::getAxisHorizontal();
            if (!en::isZero(input)) {
                currentRotation += input * player.rotationSpeed * dt;
                tf.setRotation(currentRotation);
            }
        }

        {
            if (accelerate) {
                rb.velocity += en::getForward(tf.getGlobalTransform()) * player.acceleration * dt;
            } else if (!en::isZero(rb.velocity)) {
                rb.velocity -= en::normalized(rb.velocity) * std::min(player.drag * dt, en::magnitude(rb.velocity));
            }
        }

        {
            if (en::magnitude(rb.velocity) > player.maxSpeed) {
                en::normalize(rb.velocity) *= player.maxSpeed;
            }
        }

        if (player.exhaustParticleSystem) {
            player.exhaustParticleSystem->setIsEmissionActive(accelerate);
        }
    }

    System::update(dt);
}
