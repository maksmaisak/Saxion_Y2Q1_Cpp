//
// Created by Maksym Maisak on 18/10/18.
//

#include "Factory.h"
#include "PlayerController.h"
#include "DrawableRenderer.h"
#include "ParticleSystem.h"

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

namespace game {

    std::shared_ptr<Entity> makePlayer(Engine& engine) {

        auto pPlayer = engine.makeEntity();

        sf::Vector2f size = engine.getWindow().getView().getSize();
        pPlayer->setPosition(size.x / 2.f, size.y * 3.f / 4.f);
        {
            auto r = pPlayer->add<DrawableRenderer>(makePlayerShape());

            auto pExhaust = engine.makeEntity();
            engine.addChild(pPlayer, pExhaust);
            pExhaust->move(-20.f, 0);
            auto pExhaustParticleSystem = pExhaust->add<ParticleSystem>(10000);
            {
                auto pParticleDrawable = std::make_shared<sf::CircleShape>(4.f, 3);
                pParticleDrawable->setOrigin(0.5f, 0.5f);
                pExhaustParticleSystem->setDrawable(pParticleDrawable);

                auto settings = pExhaustParticleSystem->getSettings();
                settings.emissionInterval = sf::microseconds(200);
                settings.emissionRadius = 10.f;
                settings.startVelocity.x = -1000.f;
                settings.startVelocityRandomness = 200.f;
                settings.particleLifetime = sf::seconds(1);
                pExhaustParticleSystem->setSettings(settings);
            }

            pPlayer->add<PlayerController>()->setEngineExhaustParticles(pExhaustParticleSystem);
        }

        return pPlayer;
    }
}

