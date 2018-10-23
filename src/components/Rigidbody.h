//
// Created by Maksym Maisak on 17/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RIGIDBODY_H
#define SAXION_Y2Q1_CPP_RIGIDBODY_H

#include <SFML/Graphics.hpp>

struct Rigidbody {

    sf::Vector2f velocity;
    float radius = 10.f;
    float invMass = 1.f;
    float bounciness = 1.f;
};


#endif //SAXION_Y2Q1_CPP_RIGIDBODY_H