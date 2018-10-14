#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <memory>
#include "Engine.h"
#include "SpriteRenderer.h"
#include "DrawableRenderer.h"
#include "Player.h"
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

    auto pPlayer = engine.makeEntity<Player>();
    pPlayer->setPosition(width / 2, height * 3 / 4);

    auto pRenderer = engine.makeEntity<DrawableRenderer>(makePlayerShape());
    engine.addChild(pPlayer, pRenderer);

    auto pParticles = engine.makeEntity<ParticleSystem>();
    engine.addChild(pPlayer, pParticles);
    pParticles->move(-40.f, 0);

    auto particle = std::make_shared<sf::CircleShape>(1.f, 3);
    particle->setOrigin(0.5f, 0.5f);
    pParticles->setDrawable(particle);

    auto settings = pParticles->getSettings();
    settings.emissionInterval = sf::microseconds(100);
    settings.emissionRadius = 10.f;
    settings.startVelocity.x = -1000.f;
    settings.startVelocityRandomness = 200.f;
    settings.particleLifetime = sf::seconds(2);
    pParticles->setSettings(settings);

    pPlayer->setEngineExhaustParticles(pParticles);

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
