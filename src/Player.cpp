//
// Created by Maksym Maisak on 27/9/18.
//

#include "Player.h"
#include "InputHelper.h"
#include <iostream>

Player::Player() {

    std::cout << "Player()" << std::endl;

    _texture.loadFromFile("assets/player.png");
    _sprite.setTexture(_texture);
    _sprite.setScale(0.125f, 0.125f);
}

void Player::draw_self(sf::RenderTarget& renderTarget, const sf::Transform& transform) const {

    renderTarget.draw(_sprite, transform);
}

void Player::update(float dt) {

    sf::Vector2f input = InputHelper::getMoveInput();

    _position += input * _movementSpeed * dt;

    _sprite.setPosition(_position);
}
