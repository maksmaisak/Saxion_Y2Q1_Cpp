//
// Created by Maksym Maisak on 27/9/18.
//

#include <iostream>
#include <cmath>
#include "Player.h"
#include "Input.h"
#include "Math.h"

Player::Player() {

    std::cout << "Player()" << std::endl;

    setRotation(-90.f);
}

bool shouldAccelerate();
sf::Vector2f getDirection(float angle);

void Player::update(float dt) {

    float currentRotation = getRotation();

    float input = en::getAxisHorizontal();
    if (!en::isZero(input)) {
        currentRotation += input * m_rotationSpeed * dt;
        setRotation(currentRotation);
    }

    if (shouldAccelerate()) {
        m_velocity += getDirection(currentRotation) * m_acceleration * dt;
    } else if(!en::isZero(m_velocity)) {
        m_velocity -= en::normalized(m_velocity) * std::min(m_drag * dt, en::magnitude(m_velocity));
    }

    move(m_velocity * dt);
}

inline bool shouldAccelerate() {

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

inline sf::Vector2f getDirection(float angle) {

    return {
        std::cos(angle * en::DEG2RAD),
        std::sin(angle * en::DEG2RAD)
    };
}