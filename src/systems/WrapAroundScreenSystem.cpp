//
// Created by Maksym Maisak on 23/10/18.
//

#include "WrapAroundScreenSystem.h"
#include "Engine.h"
#include "EntityRegistry.h"
#include "Transformable.h"

void WrapAroundScreenSystem::update(float dt) {

    sf::Vector2f viewSize = m_engine.getWindow().getView().getSize();

    for (Entity e : m_registry.with<en::Transformable>()) {

        auto& tf = m_registry.get<en::Transformable>(e);
        if (tf.getParent().has_value()) continue;

        sf::Vector2f position = tf.getPosition();
        while (position.x < 0) position.x += viewSize.x;
        while (position.y < 0) position.y += viewSize.y;
        while (position.x > viewSize.x) position.x -= viewSize.x;
        while (position.y > viewSize.y) position.y -= viewSize.y;
        tf.setPosition(position);
    }
}
