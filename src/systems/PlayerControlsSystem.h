//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_PLAYERCONROLSSYSTEM_H
#define SAXION_Y2Q1_CPP_PLAYERCONROLSSYSTEM_H

#include "System.h"
#include "Player.h"
#include "Transformable.h"

class PlayerControlsSystem : public System {

    using System::System;
public:
    void update(float dt) override;
};


#endif //SAXION_Y2Q1_CPP_PLAYERCONROLSSYSTEM_H
