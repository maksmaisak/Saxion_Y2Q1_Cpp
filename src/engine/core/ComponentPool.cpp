//
// Created by Maksym Maisak on 26/10/18.
//

#include "ComponentPool.h"
#include <limits>

namespace en {

    bool ComponentPoolBase::contains(en::Entity entity) {

        if (entity >= m_entityToIndex.size()) return false;
        const index_type index = m_entityToIndex[entity];
        if (index >= m_indexToEntity.size()) return false;
        return m_indexToEntity[index] == entity;
    }

    ComponentPoolBase::index_type ComponentPoolBase::insert(en::Entity entity) {

        assert(!contains(entity));
        if (entity >= m_entityToIndex.size()) {
            m_entityToIndex.resize(entity + 1);
        }

        const index_type index = m_indexToEntity.size();
        m_entityToIndex[entity] = index;
        m_indexToEntity.push_back(entity);
        return index;
    }

    ComponentPoolBase::index_type ComponentPoolBase::remove(en::Entity entity) {

        if (!contains(entity)) return nullIndex;

        assert(entity < m_entityToIndex.size());
        const index_type index = m_entityToIndex[entity];
        const en::Entity lastEntity = m_indexToEntity.back();

        // Swap and pop.
        // Overwrite the entity with the last entity, adjust the indices,
        // then remove the last entity, which is now duplicate.
        m_indexToEntity[index] = lastEntity;
        m_entityToIndex[lastEntity] = index;
        m_entityToIndex[entity] = nullIndex;
        m_indexToEntity.pop_back();

        return index;
    }
}
