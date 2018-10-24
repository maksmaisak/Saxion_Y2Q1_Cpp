//
// Created by Maksym Maisak on 24/10/18.
//

#include "BreakAsteroidSystem.h"
#include "Asteroid.h"
#include "Player.h"

void BreakAsteroidSystem::receive(const en::Collision& info) {

    Entity asteroid = nullEntity;
    Entity player = nullEntity;

    if (m_registry.tryGet<Asteroid>(info.a) && m_registry.tryGet<Player>(info.b)) {
        asteroid = info.a;
        player = info.b;
    } else if (m_registry.tryGet<Asteroid>(info.b) && m_registry.tryGet<Player>(info.a)) {
        asteroid = info.b;
        player = info.a;
    } else return;

    m_registry.destroy(asteroid);
}
