//
// Created by Maksym Maisak on 27/9/18.
//

#include "Player.h"
#include "InputHelper.h"

Player::Player() {
    
    _texture.loadFromFile("assets/player.png");
    _sprite.setTexture(_texture);
    _sprite.setScale(0.125f, 0.125f);
}

const sf::Drawable& Player::getDrawable() const {
    return _sprite;
}

void Player::update(float dt) {

    sf::Vector2f input = InputHelper::getMoveInput();

    _position += input * _movementSpeed * dt;

    _sprite.setPosition(_position);
}
