//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITYEVENTS_H
#define SAXION_Y2Q1_CPP_ENTITYEVENTS_H

#include "Entity.h"

struct EntityCreated {
    Entity entity;
};

struct EntityWillBeDestroyed {
    Entity entity;
};

#endif //SAXION_Y2Q1_CPP_ENTITYEVENTS_H
