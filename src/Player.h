//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_PLAYER_H
#define SAXION_Y2Q1_CPP_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EngineCallbacks.h"

class Player : public Entity, public Update {

public:
    Player();
    void update(float dt);

private:
    float _movementSpeed = 20.0f;
};

#endif //SAXION_Y2Q1_CPP_PLAYER_H
