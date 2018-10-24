//
// Created by Maksym Maisak on 20/10/18.
//

#include <SFML/Graphics.hpp>
#include "PhysicsSystem.h"
#include "Transformable.h"
#include "Rigidbody.h"
#include "PhysicsUtils.h"
#include "Messaging.h"
#include "Collision.h"

void PhysicsSystem::update(float dt) {

    auto view = m_registry.with<Rigidbody, en::Transformable>();
    for (Entity entity : view) {

        auto& rb = m_registry.get<Rigidbody>(entity);
        auto& tf = m_registry.get<en::Transformable>(entity);

        sf::Vector2f movement = rb.velocity * dt;

        bool didCollide = false;
        for (Entity other : view) {

            if (entity == other) continue;

            auto& otherRb = m_registry.get<Rigidbody>(other);
            auto& otherTf = m_registry.get<en::Transformable>(other);

            std::optional<en::Hit> hit = en::circleVsCircleContinuous(
                tf.getPosition(), rb.radius, movement,
                otherTf.getPosition(), otherRb.radius
            );

            if (hit.has_value()) {

                en::resolve(
                    rb.velocity, rb.invMass,
                    otherRb.velocity, otherRb.invMass,
                    hit->normal, std::min(rb.bounciness, otherRb.bounciness)
                );
                tf.move(movement * hit->timeOfImpact);
                didCollide = true;

                Receiver<en::Collision>::accept({*hit, entity, other});

                break;
            }
        }

        if (!didCollide) {
            tf.move(movement);
        }
    }
}
