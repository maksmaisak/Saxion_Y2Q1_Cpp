//
// Created by Maksym Maisak on 18/10/18.
//

#include "Factory.h"
#include "PlayerController.h"
#include "DrawableRenderer.h"
#include "ParticleSystem.h"
#include "Transformable.h"

std::shared_ptr<sf::Drawable> makePlayerShape() {

    auto pShape = std::make_shared<sf::ConvexShape>(4);

    pShape->setPoint(0, { 70,  0 });
    pShape->setPoint(1, {-70,  50});
    pShape->setPoint(2, {-50,  0 });
    pShape->setPoint(3, {-70, -50});

    pShape->setScale(0.5f, 0.5f);

    pShape->setFillColor(sf::Color::Black);
    pShape->setOutlineThickness(4.f);

    return pShape;
}

void setPosition(Engine& engine, Actor& player) {

    sf::Vector2f size = engine.getWindow().getView().getSize();
    player.add<en::Transformable>().setPosition(size.x / 2.f, size.y * 3.f / 4.f);
}

void addExhaust(Engine& engine, Actor& player) {

    Actor& exhaust = engine.makeActor();
    auto& tf = exhaust.add<en::Transformable>();
    tf.move(-200.f, 0);
    engine.setParent(exhaust, player);

    auto& exhaustParticleSystem = player.add<ParticleSystem>(10000);
    {
        auto pParticleDrawable = std::make_shared<sf::CircleShape>(4.f, 3);
        pParticleDrawable->setOrigin(0.5f, 0.5f);
        exhaustParticleSystem.setDrawable(pParticleDrawable);

        auto settings = exhaustParticleSystem.getSettings();
        settings.emissionInterval = sf::microseconds(400);
        settings.emissionRadius = 10.f;
        settings.startVelocity.x = -1000.f;
        settings.startVelocityRandomness = 100.f;
        settings.particleLifetime = sf::seconds(0.5f);
        exhaustParticleSystem.setSettings(settings);
    }
}

namespace game {

    Entity makePlayer(Engine& engine) {

        EntityRegistry& registry = engine.getRegistry();

        Actor& player = engine.makeActor();
        {
            setPosition(engine, player);
            player.add<std::shared_ptr<sf::Drawable>>(makePlayerShape());

            Actor& exhaust = engine.makeActor();
            auto& tf = registry.add<en::Transformable>(exhaust, &registry);
            tf.move(-20.f, 0);
            engine.setParent(exhaust, player);

            auto& exhaustParticleSystem = exhaust.add<ParticleSystem>(10000);
            {
                auto pParticleDrawable = std::make_shared<sf::CircleShape>(4.f, 3);
                pParticleDrawable->setOrigin(0.5f, 0.5f);
                exhaustParticleSystem.setDrawable(pParticleDrawable);

                auto settings = exhaustParticleSystem.getSettings();
                settings.emissionInterval = sf::microseconds(400);
                settings.emissionRadius = 10.f;
                settings.startVelocity.x = -1000.f;
                settings.startVelocityRandomness = 100.f;
                settings.particleLifetime = sf::seconds(0.5f);
                exhaustParticleSystem.setSettings(settings);
            }

            //registry.add<PlayerController>(player)->setEngineExhaustParticles(pExhaustParticleSystem);
        }

        player.add<PlayerController>(player);

        return player;
    }
}

