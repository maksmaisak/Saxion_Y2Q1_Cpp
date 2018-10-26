//
// Created by Maksym Maisak on 26/10/18.
//

#include "SparseSet.h"

bool SparseSet::contains(en::Entity entity) {

    assert(entity < m_entityToIndex.size());
    return m_indexToEntity[m_entityToIndex[entity]] != en::nullEntity;
}