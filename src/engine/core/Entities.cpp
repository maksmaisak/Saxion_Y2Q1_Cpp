//
// Created by Maksym Maisak on 27/10/18.
//

#include "Entities.h"

namespace en {

    Entity Entities::add() {

        const Entity entity = m_entities.size();
        m_entities.push_back(entity);
        return entity;
    }

    void Entities::remove(Entity entity) {

        assert(entity < m_entities.size());

        m_entities[entity] = nullEntity;
        m_nextFree = entity;
    }
}
