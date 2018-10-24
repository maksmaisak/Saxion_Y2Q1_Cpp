//
// Created by Maksym Maisak on 21/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITYREGISTRY_H
#define SAXION_Y2Q1_CPP_ENTITYREGISTRY_H

#include <memory>
#include <utility>
#include <set>
#include <typeindex>
#include <iostream>
#include "Entity.h"
#include "ComponentPool.h"
#include "EntitiesView.h"
#include "Messaging.h"

#include "Transformable.h"

class EntityRegistry {

public:

    Entity makeEntity();
    void destroy(Entity entity);

    template<class TComponent>
    TComponent& get(Entity entity) const;

    template<class TComponent>
    TComponent* tryGet(Entity entity) const;

    template<class TComponent>
    TComponent& add(Entity entity, TComponent component);

    template<class TComponent, typename... Args>
    inline TComponent& add(Entity entity, Args&&... args);

    template<typename... TComponent>
    EntitiesView<TComponent...> with();

private:

    Entity m_nextId = 1;
    std::set<Entity> m_entities;
    mutable std::map<std::type_index, std::unique_ptr<ComponentPoolBase>> m_componentPools;

    template<typename TComponent>
    inline ComponentPool<TComponent>& getPool() const;
};

template<typename T, typename Base>
inline constexpr bool inherits = std::is_base_of<Base, T>::value;

template<class T>
inline std::type_index getTypeIndex() {
    return std::type_index(typeid(T));
}

template<class TComponent>
TComponent& EntityRegistry::get(const Entity entity) const {

    ComponentPool<TComponent>& pool = getPool<TComponent>();

    assert(pool.count(entity) == 1);
    return pool.at(entity);
}

template<class TComponent>
TComponent* EntityRegistry::tryGet(Entity entity) const {

    ComponentPool<TComponent>& pool = getPool<TComponent>();

    auto it = pool.find(entity);
    if (it == pool.end()) return nullptr;

    return &it->second;
}

template<class TComponent>
TComponent& EntityRegistry::add(Entity entity, TComponent component) {

    ComponentPool<TComponent>& pool = getPool<TComponent>();

    assert(pool.count(entity) == 0);
    auto [it, didAdd] = pool.emplace(entity, component);
    assert(didAdd);

    Receiver<ComponentAdded<TComponent>>::accept({entity, it->second});

    return it->second;
}

template<class TComponent, typename... Args>
TComponent& EntityRegistry::add(Entity entity, Args&&... args) {

    ComponentPool<TComponent>& pool = getPool<TComponent>();

    assert(pool.count(entity) == 0);
    auto [it, didAdd] = pool.try_emplace(entity, std::forward<Args>(args)...);
    assert(didAdd);

    Receiver<ComponentAdded<TComponent>>::accept({entity, it->second});

    return it->second;
}

/// TEMP m_registry is assigned here until it can be done in an event handler (TODO)
template<>
inline en::Transformable& EntityRegistry::add<en::Transformable>(Entity entity) {

    ComponentPool<en::Transformable>& pool = getPool<en::Transformable>();

    assert(pool.count(entity) == 0);
    auto [it, didAdd] = pool.try_emplace(entity, this);
    assert(didAdd);

    Receiver<ComponentAdded<en::Transformable>>::accept({entity, it->second});

    return it->second;
}

template<typename... TComponent>
EntitiesView<TComponent...> EntityRegistry::with() {

    return EntitiesView<TComponent...>(m_entities, getPool<TComponent>()...);
}

template<typename TComponent>
inline ComponentPool<TComponent>& EntityRegistry::getPool() const {

    // TODO Do something faster than std::set for this.
    const std::type_index key = getTypeIndex<TComponent>();

    auto it = m_componentPools.find(key);
    if (it == m_componentPools.cend()) {

        it = m_componentPools.emplace(key, new ComponentPool<TComponent>()).first;
        std::clog << "Created a component pool for " << typeid(TComponent).name() << std::endl;
    }

    return *static_cast<ComponentPool<TComponent>*>(it->second.get());
}

#endif //SAXION_Y2Q1_CPP_ENTITYREGISTRY_H
