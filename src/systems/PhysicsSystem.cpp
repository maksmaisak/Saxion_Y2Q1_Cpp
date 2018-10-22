//
// Created by Maksym Maisak on 20/10/18.
//

#include <SFML/Graphics.hpp>
#include "PhysicsSystem.h"
#include "Rigidbody.h"

void PhysicsSystem::update(float dt) {

    auto& registry = m_engine.getRegistry();

    for (Entity entity : m_engine.getRegistry().with<Rigidbody, sf::Transformable>()) {

        auto& rb = registry.get<Rigidbody>(entity);
        auto& transformable = registry.get<sf::Transformable>(entity);

        transformable.move(rb.m_velocity * dt);
    }
}
