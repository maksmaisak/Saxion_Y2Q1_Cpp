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

template<typename TComponent>
struct ComponentAdded {
    Entity entity;
    TComponent& component;
};

template<typename TComponent>
struct ComponentWillBeRemoved {
    Entity entity;
    TComponent& component;
};

#endif //SAXION_Y2Q1_CPP_ENTITYEVENTS_H
