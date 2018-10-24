//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COMPONENTPOOL_H
#define SAXION_Y2Q1_CPP_COMPONENTPOOL_H

#include <map>
#include <vector>
#include "Entity.h"
#include "Messaging.h"
#include "EntityEvents.h"

class ComponentPoolBase {};

template<typename TComponent>
class ComponentPool : public ComponentPoolBase, public std::map<Entity, TComponent>, Receiver<EntityWillBeDestroyed> {

    // TEMP Relies on global events, breaks down if there are multiple registries.
    // TODO Have base class have an erase function.
    void receive(const EntityWillBeDestroyed& info) override {
        std::map<Entity, TComponent>::erase(info.entity);
    }
};

#endif //SAXION_Y2Q1_CPP_COMPONENTPOOL_H
