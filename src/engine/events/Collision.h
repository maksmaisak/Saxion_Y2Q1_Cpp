//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COLLISION_H
#define SAXION_Y2Q1_CPP_COLLISION_H

#include "Entity.h"
#include <optional>
#include <tuple>
#include "PhysicsUtils.h"
#include "EntityRegistry.h"

namespace en {

    struct Collision {
        en::Hit hit;
        en::Entity a = nullEntity;
        en::Entity b = nullEntity;
    };

    template<typename TComponentA, typename TComponentB>
    std::tuple<bool, Entity, Entity> getCollision(const EntityRegistry& registry, const Collision& collision) {

        if (registry.tryGet<TComponentA>(collision.a) && registry.tryGet<TComponentB>(collision.b)) {
            return std::make_tuple(true, collision.a, collision.b);
        }

        if constexpr (!std::is_same_v<TComponentA, TComponentB>) {
            if (registry.tryGet<TComponentA>(collision.b) && registry.tryGet<TComponentB>(collision.a)) {
                return std::make_tuple(true, collision.b, collision.a);
            }
        }

        return std::make_tuple(false, nullEntity, nullEntity);
    }
}

#endif //SAXION_Y2Q1_CPP_COLLISION_H
