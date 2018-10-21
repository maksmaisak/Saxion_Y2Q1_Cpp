//
// Created by Maksym Maisak on 18/10/18.
//

#include <engine/DrawableRenderer.h>
#include "Factory.h"
#include "Asteroid.h"
#include "MyMath.h"

const std::size_t NUM_VERTICES = 10;

std::shared_ptr<sf::Drawable> makeAsteroidShape() {

    auto pShape = std::make_shared<sf::ConvexShape>(NUM_VERTICES);

    for (std::size_t i = 0; i < NUM_VERTICES; ++i) {
        pShape->setPoint(i, en::polar2Cartesian((en::PI2 * i) / NUM_VERTICES, en::random(40.f, 60.f)));
    }

    pShape->setFillColor(sf::Color::Transparent);
    pShape->setOutlineThickness(4.f);

    return pShape;
}

namespace game {

    std::shared_ptr<Entity> makeAsteroid(Engine& engine) {

         auto pEntity = engine.makeEntity();
         engine.add<DrawableRenderer>(*pEntity, makeAsteroidShape());
         engine.add<Asteroid>(*pEntity);

         sf::Vector2f position = engine.getWindow().getView().getSize();
         position.x *= en::random();
         position.y *= en::random();
         pEntity->setPosition(position);

        return pEntity;
    }
}
