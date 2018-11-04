//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COLLISION_H
#define SAXION_Y2Q1_CPP_COLLISION_H

#include "Entity.h"
#include <optional>
#include <tuple>
#include "PhysicsUtils.h"

namespace en {

    struct Collision {
        en::Hit hit;
        en::Entity a = nullEntity;
        en::Entity b = nullEntity;
    };

    template<typename TComponentA, typename TComponentB>
    std::tuple<bool, Entity, Entity> getCollision(const en::Collision& collision) {
        throw "not implemented";
    }
}

#endif //SAXION_Y2Q1_CPP_COLLISION_H
