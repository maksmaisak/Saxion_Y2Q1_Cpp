//
// Created by Maksym Maisak on 18/10/18.
//

#include "Rigidbody.h"
#include "Factory.h"
#include "ParticleSystem.h"
#include "Transformable.h"
#include "Player.h"
#include "Flicker.h"

std::shared_ptr<sf::Shape> makePlayerShape() {

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

void addTransformable(Engine& engine, Entity player) {

    sf::Vector2f size = engine.getWindow().getView().getSize();
    auto& tf = engine.getRegistry().add<en::Transformable>(player);
    tf.setPosition(size.x / 2.f, size.y * 3.f / 4.f);
    tf.setRotation(-90.f);
}

Entity addExhaust(Engine& engine, Entity player) {

    EntityRegistry& registry = engine.getRegistry();

    Actor& exhaust = engine.makeActor();
    auto& tf = registry.add<en::Transformable>(exhaust, &registry);
    tf.move(-30.f, 0);
    engine.setParent(exhaust, player);

    auto& exhaustParticleSystem = exhaust.add<ParticleSystem>(10000);
    {
        auto pParticleDrawable = std::make_shared<sf::CircleShape>(4.f, 3);
        pParticleDrawable->setOrigin(0.5f, 0.5f);
        exhaustParticleSystem.setDrawable(pParticleDrawable);

        auto s = exhaustParticleSystem.getSettings();
        s.emissionInterval = sf::microseconds(400);
        s.emissionRadius = 10.f;
        s.startVelocity.x = -1000.f;
        s.startVelocityRandomness = 100.f;
        s.particleLifetime = sf::seconds(0.5f);
        exhaustParticleSystem.setSettings(s);
    }

    registry.get<Player>(player).exhaustParticleSystem = &exhaustParticleSystem;

    return exhaust;
}

namespace game {

    Entity makePlayer(Engine& engine) {

        EntityRegistry& registry = engine.getRegistry();
        Entity e = registry.makeEntity();

        addTransformable(engine, e);

        std::shared_ptr<sf::Shape> shape = makePlayerShape();
        registry.add<std::shared_ptr<sf::Drawable>>(e, shape);
        registry.add<Flicker>(e, {shape});
        registry.add<Player>(e);

        {
            auto& rb = registry.add<Rigidbody>(e);
            rb.radius = 30.f;
            rb.invMass = 1.f / 0.5f;
        }

        addExhaust(engine, e);

        return e;
    }
}

