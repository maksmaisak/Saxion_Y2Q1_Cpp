//
// Created by Maksym Maisak on 18/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ASTEROID_H
#define SAXION_Y2Q1_CPP_ASTEROID_H

#include "Engine.h"

class Asteroid : public Component {

    using Component::Component;

public:
    void update(float dt) override;

private:
    sf::Vector2f m_velocity;

    void flicker();
};


#endif //SAXION_Y2Q1_CPP_ASTEROID_H
