//
// Created by Maksym Maisak on 26/10/18.
//

#ifndef SAXION_Y2Q1_CPP_SPARSESET_H
#define SAXION_Y2Q1_CPP_SPARSESET_H

#include <vector>
#include "Entity.h"


class SparseSet {

public:
    bool contains(en::Entity entity);
    void add(en::Entity entity);
    void remove(en::Entity entity);

private:
    std::vector<en::Entity> m_indexToEntity;
    std::vector<std::vector<en::Entity>::size_type> m_entityToIndex;
};

template<typename TComponent>
class SparseMap : public SparseSet {

public:
    void add(en::Entity entity, TComponent component);

    template<typename... Args>
    void add(en::Entity entity, Args&&... args);

    void remove(en::Entity entity);

private:
    std::vector<TComponent> m_indexToComponent;
};

#endif //SAXION_Y2Q1_CPP_SPARSESET_H
