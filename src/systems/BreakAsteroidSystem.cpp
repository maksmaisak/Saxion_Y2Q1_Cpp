//
// Created by Maksym Maisak on 24/10/18.
//

#include "BreakAsteroidSystem.h"
#include <iostream>
#include "Asteroid.h"
#include "Bullet.h"

void BreakAsteroidSystem::receive(const en::Collision& info) {

    if (
        (m_registry.tryGet<Asteroid>(info.a) && m_registry.tryGet<Bullet>(info.b)) ||
        (m_registry.tryGet<Asteroid>(info.b) && m_registry.tryGet<Bullet>(info.a))
    ) {
        m_entitiesToDestroy.push_back(info.a);
        m_entitiesToDestroy.push_back(info.b);
    }
}

void BreakAsteroidSystem::update(float dt) {

    for (Entity e : m_entitiesToDestroy) m_registry.destroy(e);

    m_entitiesToDestroy.clear();
}
