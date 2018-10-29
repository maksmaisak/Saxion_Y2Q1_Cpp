//
// Created by Maksym Maisak on 29/10/18.
//

#include "PlayerDeathSystem.h"
#include <optional>
#include <tuple>
#include "Engine.h"
#include "Asteroid.h"
#include "Player.h"
#include "Factory.h"

std::optional<std::tuple<en::Entity, en::Entity>> getPlayerAsteroidCollision(const en::EntityRegistry& registry, const en::Collision& collision){

    en::Entity asteroidEntity = collision.a;
    en::Entity playerEntity   = collision.b;

    auto* asteroidPtr = registry.tryGet<Asteroid>(asteroidEntity);
    auto* playerPtr   = registry.tryGet<Player>  (playerEntity);

    if (!asteroidPtr || !playerPtr) {
        std::swap(asteroidEntity, playerEntity);
        asteroidPtr = registry.tryGet<Asteroid>(asteroidEntity);
        playerPtr   = registry.tryGet<Player>  (playerEntity);

        if (!asteroidPtr || !playerPtr) return std::nullopt;
    }

    return std::make_tuple(asteroidEntity, playerEntity);
}

void PlayerDeathSystem::receive(const en::Collision& collision) {

    auto result = getPlayerAsteroidCollision(m_registry, collision);
    if (!result.has_value()) return;
    auto [player, asteroid] = *result;

    m_registry.destroy(player);
    m_shouldRestart = true;
}

void PlayerDeathSystem::update(float dt) {

    if (!m_shouldRestart) return;

    m_registry.destroyAll();
    game::makeMainLevel(m_engine);

    m_shouldRestart = false;
}
