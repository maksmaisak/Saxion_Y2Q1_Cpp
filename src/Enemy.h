//
// Created by Maksym Maisak on 5/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENEMY_H
#define SAXION_Y2Q1_CPP_ENEMY_H

#include "Entity.h"
#include "EngineCallbacks.h"

class Enemy : public Entity, public Update {

public:
    void update(float dt);
};


#endif //SAXION_Y2Q1_CPP_ENEMY_H
