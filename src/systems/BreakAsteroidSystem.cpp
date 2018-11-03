//
// Created by Maksym Maisak on 24/10/18.
//

#include "BreakAsteroidSystem.h"
#include <iostream>
#include <optional>
#include <tuple>
#include <components/Rigidbody.h>
#include "Asteroid.h"
#include "Bullet.h"
#include "Factory.h"

std::optional<std::tuple<en::Entity, en::Entity, Asteroid&>> getAsteroidBulletCollision(const en::EntityRegistry& registry, const en::Collision& collision){

    en::Entity asteroidEntity = collision.a;
    en::Entity bulletEntity   = collision.b;

    auto* asteroidPtr = registry.tryGet<Asteroid>(asteroidEntity);
    auto* bulletPtr   = registry.tryGet<Bullet>  (bulletEntity);

    if (!asteroidPtr || !bulletPtr) {
        std::swap(asteroidEntity, bulletEntity);
        asteroidPtr = registry.tryGet<Asteroid>(asteroidEntity);
        bulletPtr   = registry.tryGet<Bullet>  (bulletEntity);

        if (!asteroidPtr || !bulletPtr) return std::nullopt;
    }

    return std::make_tuple(asteroidEntity, bulletEntity, std::ref(*asteroidPtr));
}

void split(en::Engine& engine, en::EntityRegistry& registry, en::Entity asteroidEntity, const Asteroid& asteroid) {

    assert(asteroid.size > Asteroid::Size::Small);
    const auto piecesSize = (Asteroid::Size)((std::size_t)asteroid.size - 1);
    const Asteroid::Config& piecesConfig = Asteroid::getConfig(piecesSize);

    const auto& transform = registry.get<en::Transformable>(asteroidEntity).getGlobalTransform();
    sf::Vector2f position = en::getPosition(transform);
    sf::Vector2f velocity = registry.get<en::Rigidbody>(asteroidEntity).velocity;

    const std::size_t NUM_PIECES = 2;
    const float radius = piecesConfig.averageRadius + piecesConfig.radiusRange;
    const float startAngle = en::random(0.f, en::PI2);
    for (std::size_t i = 0; i < NUM_PIECES; ++i) {

        const float angle = startAngle + en::PI2 * (float)i / NUM_PIECES;
        const sf::Vector2f offset = en::polar2Cartesian(angle, radius);

        const sf::Vector2f relativeVelocity = en::normalized(offset) * 100.f;

        game::makeAsteroid(engine, piecesSize, position + offset, velocity + relativeVelocity);
    }
}

void BreakAsteroidSystem::receive(const en::Collision& collision) {

    auto result = getAsteroidBulletCollision(*m_registry, collision);
    if (!result.has_value()) return;
    auto [asteroidEntity, bulletEntity, asteroid] = *result;

    m_entitiesToDestroy.push_back(asteroidEntity);
    m_entitiesToDestroy.push_back(bulletEntity);

    if (asteroid.size > Asteroid::Size::Small) {
        split(*m_engine, *m_registry, asteroidEntity, asteroid);
    }
}

void BreakAsteroidSystem::update(float dt) {

    for (en::Entity e : m_entitiesToDestroy) m_registry->destroy(e);

    m_entitiesToDestroy.clear();
}
