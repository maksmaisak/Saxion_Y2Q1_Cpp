//
// Created by Maksym Maisak on 18/10/18.
//

#ifndef SAXION_Y2Q1_CPP_FACTORY_H
#define SAXION_Y2Q1_CPP_FACTORY_H

#include "Engine.h"

namespace game {

    Entity makePlayer(Engine& engine);
    Entity makeAsteroid(Engine& engine);
};


#endif //SAXION_Y2Q1_CPP_FACTORY_H
