//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COLLISION_H
#define SAXION_Y2Q1_CPP_COLLISION_H

#include "Entity.h"
#include "PhysicsUtils.h"

namespace en {

    struct Collision {
        en::Hit hit;
        Entity a = nullEntity;
        Entity b = nullEntity;
    };
}

#endif //SAXION_Y2Q1_CPP_COLLISION_H
