//
// Created by Maksym Maisak on 20/10/18.
//

#ifndef SAXION_Y2Q1_CPP_PHYSICSSYSTEM_H
#define SAXION_Y2Q1_CPP_PHYSICSSYSTEM_H

#include "System.h"
#include "Engine.h"

class PhysicsSystem : public System {

public:
    explicit PhysicsSystem(Engine& engine) : System(engine) {}
    void update(float dt) override;
};


#endif //SAXION_Y2Q1_CPP_PHYSICSSYSTEM_H
