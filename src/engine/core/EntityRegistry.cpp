//
// Created by Maksym Maisak on 21/10/18.
//

#include "EntityRegistry.h"

Entity EntityRegistry::makeEntity() {

    auto [iterator, didInsert] = m_entities.insert(m_nextId++);
    assert(didInsert);
    return *iterator;
}

void EntityRegistry::destroy(Entity entity) {
    
    m_entities.erase(entity);

    /*for (auto& kvp : m_componentPools) {
        kvp.second->erase(entity);
    }*/
    throw "component removal not implemented";
}
