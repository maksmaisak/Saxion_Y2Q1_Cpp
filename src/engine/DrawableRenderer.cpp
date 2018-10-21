#include <utility>

//
// Created by Maksym Maisak on 14/10/18.
//

#include "DrawableRenderer.h"

DrawableRenderer::DrawableRenderer(Entity* pEntity, std::shared_ptr<sf::Drawable> drawable) :
    Component(pEntity),
    m_drawable(std::move(drawable))
    {}

void DrawableRenderer::draw(sf::RenderTarget& renderTarget) {

    renderTarget.draw(*m_drawable, m_Entity.getGlobalTransform());
}

const std::shared_ptr<sf::Drawable>& DrawableRenderer::getDrawable() const {

    return m_drawable;
}
