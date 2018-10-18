//
// Created by Maksym Maisak on 11/10/18.
//

#ifndef SAXION_Y2Q1_CPP_VECTORMATH_H
#define SAXION_Y2Q1_CPP_VECTORMATH_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace en {

    const float PI = 3.14159265359f;
    const float PI2 = PI * 2.0f;
    const float RAD2DEG = 360.0f / PI2;
    const float DEG2RAD = PI2 / 360.0f;
    const float EPSILON = 0.001f;

    float angleDegrees(sf::Vector2f vec);
    sf::Vector2f& normalize(sf::Vector2f& vec);
    sf::Vector2f normalized(const sf::Vector2f& vec);
    float magnitude(const sf::Vector2f& vec);
    float sqrMagnitude(const sf::Vector2f& vec);
    bool isZero(float value);
    bool isZero(const sf::Vector2f& vec);
    sf::Vector2f polar2Cartesian(float angle, float radius);

    float random(float min = 0.f, float max = 1.f);
    sf::Vector2f randomInCircle(float radius = 1.f);
}


#endif //SAXION_Y2Q1_CPP_VECTORMATH_H
