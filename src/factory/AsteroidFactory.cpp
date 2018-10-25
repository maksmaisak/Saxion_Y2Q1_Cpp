//
// Created by Maksym Maisak on 18/10/18.
//

#include "Factory.h"
#include "Rigidbody.h"
#include "Flicker.h"
#include "MyMath.h"
#include "Asteroid.h"
#include "DrawInfo.h"

const std::size_t NUM_VERTICES = 10;
const float AVERAGE_RADIUS = 50.f;
const float RADIUS_RANGE = 10.f;

std::shared_ptr<sf::Shape> makeAsteroidShape() {

    auto pShape = std::make_shared<sf::ConvexShape>(NUM_VERTICES);

    for (std::size_t i = 0; i < NUM_VERTICES; ++i) {

        sf::Vector2f point = en::polar2Cartesian(
            (en::PI2 * i) / NUM_VERTICES,
            AVERAGE_RADIUS + en::random(-RADIUS_RANGE, RADIUS_RANGE)
        );

        pShape->setPoint(i, point);
    }

    pShape->setFillColor(sf::Color::Transparent);
    pShape->setOutlineThickness(4.f);

    return pShape;
}

namespace game {

    Entity makeAsteroid(Engine& engine) {

        EntityRegistry& registry = engine.getRegistry();

        Entity e = registry.makeEntity();

        registry.add<Asteroid>(e);

        std::shared_ptr<sf::Shape> shape = makeAsteroidShape();
        registry.add<en::DrawInfo>(e, shape);
        registry.add<Flicker>(e, shape);

        auto& rb = registry.add<en::Rigidbody>(e);
        rb.velocity = en::randomInCircle(400.f);
        rb.radius = AVERAGE_RADIUS;

        sf::Vector2f position = engine.getWindow().getView().getSize();
        position.x *= en::random();
        position.y *= en::random();
        registry.add<en::Transformable>(e).setPosition(position);

        return e;
    }
}
