//
// Created by Maksym Maisak on 23/10/18.
//

#ifndef SAXION_Y2Q1_CPP_WRAPAROUNDSCREENSYSTEM_H
#define SAXION_Y2Q1_CPP_WRAPAROUNDSCREENSYSTEM_H

#include "System.h"

class WrapAroundScreenSystem : public System {

    using System::System;

public:
    void update(float dt) override;
};

#endif //SAXION_Y2Q1_CPP_WRAPAROUNDSCREENSYSTEM_H
