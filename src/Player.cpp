//
// Created by Maksym Maisak on 27/9/18.
//

#include "Player.h"
#include "InputHelper.h"
#include <iostream>

Player::Player() {

    std::cout << "Player()" << std::endl;
}

void Player::update(float dt) {

    sf::Vector2f input = InputHelper::getMoveInput();

    sf::Vector2f position = getPosition();
    position += input * _movementSpeed * dt;
    setPosition(position);
}
