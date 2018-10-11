//
// Created by Maksym Maisak on 11/10/18.
//

#include "Math.h"
#include <cmath>

namespace en {

    float angleDegrees(sf::Vector2f vec) {

        return std::atan2f(vec.y, vec.x) * RAD2DEG;
    }

    bool isZero(float value) {

        return abs(value) < EPSILON;
    }

    bool isZero(const sf::Vector2f& vec) {

        return isZero(vec.x) && isZero(vec.y);
    }

    sf::Vector2f& normalize(sf::Vector2f& vec) {

        float magnitude = hypot(vec.x, vec.y);
        vec.x /= magnitude;
        vec.y /= magnitude;
        return vec;
    }

    sf::Vector2f normalized(const sf::Vector2f& vec) {

        sf::Vector2f result = vec;
        return normalize(result);
    }

    float magnitude(const sf::Vector2f& vec) {

        return hypotf(vec.x, vec.y);
    }

    float sqrMagnitude(const sf::Vector2f& vec) {

        return vec.x * vec.x + vec.y * vec.y;
    }
}
