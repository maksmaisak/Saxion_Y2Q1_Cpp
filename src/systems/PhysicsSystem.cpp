//
// Created by Maksym Maisak on 20/10/18.
//

#include "PhysicsSystem.h"
#include "Rigidbody.h"

void PhysicsSystem::update(float dt) {

    for (auto& pEntity : m_engine->with<Rigidbody>()) {

        auto& rb = *pEntity->get<Rigidbody>();
        pEntity->setPosition(pEntity->getPosition() + rb.m_velocity * dt);
    }
}
