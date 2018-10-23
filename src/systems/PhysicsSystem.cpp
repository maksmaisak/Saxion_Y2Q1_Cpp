//
// Created by Maksym Maisak on 20/10/18.
//

#include <SFML/Graphics.hpp>
#include "PhysicsSystem.h"
#include "Transformable.h"
#include "Rigidbody.h"

void PhysicsSystem::update(float dt) {

    for (Entity entity : m_registry.with<Rigidbody, en::Transformable>()) {

        auto& rb = m_registry.get<Rigidbody>(entity);
        auto& transformable = m_registry.get<en::Transformable>(entity);

        transformable.move(rb.m_velocity * dt);
    }
}
