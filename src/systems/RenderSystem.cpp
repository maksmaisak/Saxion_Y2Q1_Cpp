//
// Created by Maksym Maisak on 22/10/18.
//

#include "RenderSystem.h"

void RenderSystem::draw() {

    auto& renderTarget = m_engine.getWindow();

    // Maybe have the iterator value be a tuple of an Entity and components instead of just an Entity?
    for (Entity e : m_registry.with<en::Transformable, std::shared_ptr<sf::Drawable>>()) {

        const auto& transform = m_registry.get<en::Transformable>(e).getGlobalTransform();
        renderTarget.draw(*m_registry.get<std::shared_ptr<sf::Drawable>>(e), transform);
    }
}
