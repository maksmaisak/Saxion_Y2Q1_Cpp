//
// Created by Maksym Maisak on 27/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITIES_H
#define SAXION_Y2Q1_CPP_ENTITIES_H

#include "Entity.h"
#include <vector>

namespace en {

    /// An efficient collection of entities with entity reuse.
    class Entities {

    public:
        Entity add();
        void remove(Entity entity);

    private:
        std::vector<Entity> m_entities;
        Entity m_nextFree = nullEntity;
    };
}

#endif //SAXION_Y2Q1_CPP_ENTITIES_H
