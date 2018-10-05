//
// Created by Maksym Maisak on 5/10/18.
//

#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const std::string& filePath) {

    _texture.loadFromFile(filePath);
    _sprite.setTexture(_texture);

    _sprite.setOrigin(0.5, 0.5);
}

void SpriteRenderer::draw(sf::RenderTarget& renderTarget) {

    renderTarget.draw(_sprite, getGlobalTransform());
}
