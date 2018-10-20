//
// Created by Maksym Maisak on 20/10/18.
//

#ifndef SAXION_Y2Q1_CPP_PHYSICSSYSTEM_H
#define SAXION_Y2Q1_CPP_PHYSICSSYSTEM_H

#include "Engine.h"

class PhysicsSystem {

public:
    void update(float dt);

private:
    Engine* m_engine;
};


#endif //SAXION_Y2Q1_CPP_PHYSICSSYSTEM_H
