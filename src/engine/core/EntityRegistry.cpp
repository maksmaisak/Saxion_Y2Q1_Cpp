//
// Created by Maksym Maisak on 21/10/18.
//

#include "EntityRegistry.h"
#include "Messaging.h"
#include "EntityEvents.h"

namespace en {

    Entity EntityRegistry::makeEntity() {

        auto [iterator, didInsert] = m_entities.insert(m_nextId++);
        assert(didInsert);

        const en::Entity entity = *iterator;
        Receiver<EntityCreated>::accept({entity});
        return entity;
    }

    void EntityRegistry::destroy(Entity entity) {

        Receiver<EntityWillBeDestroyed>::accept({entity});

        m_entities.erase(entity);

        // TODO Make ComponentPoolBase provide this functionality
    //    for (auto& kvp : m_componentPools) {
    //        kvp.second->erase(entity);
    //    }
    }

    void EntityRegistry::destroyAll() {

        for (Entity e : m_entities) Receiver<EntityWillBeDestroyed>::accept({e});
        m_entities.clear();
    }

}