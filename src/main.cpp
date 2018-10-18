#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <memory>
#include "Engine.h"
#include "DrawableRenderer.h"
#include "PlayerController.h"
#include "ParticleSystem.h"

using uint = unsigned int;

const uint width  = 1600;
const uint height = 1200;

std::shared_ptr<Entity> makePlayer(Engine& engine);
std::shared_ptr<sf::Drawable> makePlayerShape();

int main() {

    Engine engine(width, height);

    std::shared_ptr<Entity> pEntity = engine.makeEntity();
    engine.destroy(*pEntity);

    auto pPlayer = makePlayer(engine);

    engine.run();

    return 0;
}

std::shared_ptr<Entity> makePlayer(Engine& engine) {

    auto pPlayer = engine.makeEntity();
    pPlayer->setPosition(width / 2.f, height * 3.f / 4);
    {
        pPlayer->add<DrawableRenderer>(makePlayerShape());

        auto pExhaust = engine.makeEntity();
        engine.addChild(pPlayer, pExhaust);
        pExhaust->move(-40.f, 0);
        auto pExhaustParticleSystem = pExhaust->add<ParticleSystem>();
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

std::shared_ptr<sf::Drawable> makePlayerShape() {

    auto pShape = std::make_shared<sf::ConvexShape>(3);

    pShape->setPoint(0, { 100,  0 });
    pShape->setPoint(1, {-100,  50});
    pShape->setPoint(2, {-100, -50});

    pShape->setScale(0.5f, 0.5f);

    pShape->setFillColor(sf::Color::Black);
    pShape->setOutlineThickness(4.f);

    return pShape;
}
