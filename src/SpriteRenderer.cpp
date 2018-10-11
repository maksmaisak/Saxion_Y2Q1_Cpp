//
// Created by Maksym Maisak on 5/10/18.
//

#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const std::string& filePath) {

    _texture.loadFromFile(filePath);
    _sprite.setTexture(_texture);

    sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(bounds.width * 0.5f, bounds.width * 0.5f);
}

void SpriteRenderer::draw(sf::RenderTarget& renderTarget) {

    renderTarget.draw(_sprite, getGlobalTransform());
}
