//
// Created by Maksym Maisak on 14/10/18.
//

#include "DrawableRenderer.h"

DrawableRenderer::DrawableRenderer(std::shared_ptr<sf::Drawable> drawable) :
    m_drawable(drawable) {}

void DrawableRenderer::draw(sf::RenderTarget& renderTarget) {

    renderTarget.draw(*m_drawable, getGlobalTransform());
}
