//
// Created by Maksym Maisak on 29/10/18.
//

#include "PlayerDeathSystem.h"
#include <optional>
#include <tuple>
#include <components/GameOverScreen.h>
#include "Actor.h"
#include "Asteroid.h"
#include "Player.h"
#include "Factory.h"
#include "Restart.h"
#include "Destroy.h"
#include "GameOverScreen.h"

void destroyPlayer(en::Engine& engine, Entity player) {

    auto& registry = engine.getRegistry();
    registry.add<en::Destroy>(player);
    registry.get<Player>(player).exhaustParticleSystem->setIsEmissionActive(false);
    for (Entity child : registry.get<en::Transformable>(player).getChildren()) {
        engine.setParent(child, std::nullopt);
    }
}

void makeGameOverScreen(en::Engine& engine) {

    engine.makeActor().add<GameOverScreen>();
}

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

    return std::make_tuple(playerEntity, asteroidEntity);
}

void PlayerDeathSystem::receive(const en::Collision& collision) {

    if (m_isAtGameOverScreen) return;

    auto result = getPlayerAsteroidCollision(*m_registry, collision);
    if (!result.has_value()) return;
    auto [player, asteroid] = *result;

    destroyPlayer(*m_engine, player);
    makeGameOverScreen(*m_engine);

    m_engine->getScheduler().delay(sf::seconds(4.f), [this](){
        m_registry->destroyAll();
        en::Receiver<Restart>::accept({});
        game::makeMainLevel(*m_engine);
        m_isAtGameOverScreen = false;
    });
    m_isAtGameOverScreen = true;
}