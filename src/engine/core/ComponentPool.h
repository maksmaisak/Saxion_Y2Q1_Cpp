//
// Created by Maksym Maisak on 26/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COMPONENTPOOL_H
#define SAXION_Y2Q1_CPP_COMPONENTPOOL_H

#include <vector>
#include <limits>
#include "Entity.h"

namespace en {

    class ComponentPoolBase {

        static_assert(std::is_unsigned_v<en::Entity>, "A sparse set can't store signed integers.");

    public:
        using const_iterator = std::vector<en::Entity>::const_iterator;
        using iterator = const_iterator;
        using index_type = std::vector<en::Entity>::size_type;

        const index_type nullIndex = std::numeric_limits<index_type>::max();

        virtual ~ComponentPoolBase() = default;

        index_type insert(en::Entity entity);
        bool contains(en::Entity entity);
        virtual index_type remove(en::Entity entity);

        inline iterator begin() {return cbegin();}
        inline iterator end()   {return cend();  }
        inline const_iterator cbegin() {return m_indexToEntity.cbegin();}
        inline const_iterator cend()   {return m_indexToEntity.cend();  }

    protected:
        std::vector<en::Entity> m_indexToEntity;
        std::vector<index_type> m_entityToIndex;
    };

    template<typename TComponent>
    class ComponentPool : public ComponentPoolBase {

    public:
        template<typename... Args>
        std::tuple<index_type, TComponent&> insert(en::Entity entity, Args&& ... args);
        std::tuple<index_type, TComponent&> insert(en::Entity entity, const TComponent& component);
        index_type remove(en::Entity entity) override;

        TComponent& get(en::Entity entity);
        TComponent* tryGet(en::Entity entity);

    private:
        std::vector<TComponent> m_indexToComponent;
    };

    template<typename TComponent>
    template<typename... Args>
    std::tuple<ComponentPoolBase::index_type, TComponent&> ComponentPool<TComponent>::insert(en::Entity entity, Args&&... args) {

        const index_type index = ComponentPoolBase::insert(entity);
        m_indexToComponent.push_back(TComponent{std::forward<Args>(args)...});
        return std::make_tuple(index, std::ref(m_indexToComponent.back()));
    }

    template<typename TComponent>
    std::tuple<ComponentPoolBase::index_type, TComponent&> ComponentPool<TComponent>::insert(en::Entity entity, const TComponent& component) {

        const index_type index = ComponentPoolBase::insert(entity);
        m_indexToComponent.push_back(component);
        return std::make_tuple(index, std::ref(m_indexToComponent.back()));
    }

    template<typename TComponent>
    TComponent& ComponentPool<TComponent>::get(en::Entity entity) {

        assert(contains(entity));
        return m_indexToComponent[m_entityToIndex[entity]];
    }

    template<typename TComponent>
    TComponent* ComponentPool<TComponent>::tryGet(en::Entity entity) {

        if (!contains(entity)) return nullptr;
        return &m_indexToComponent[m_entityToIndex[entity]];
    }

    template<typename TComponent>
    ComponentPoolBase::index_type ComponentPool<TComponent>::remove(en::Entity entity) {

        const index_type index = ComponentPoolBase::remove(entity);
        if (index == nullIndex) return nullIndex;

        // Swap and pop to keep the storage contiguous.
        m_indexToComponent[index] = m_indexToComponent.back();
        m_indexToComponent.pop_back();

        return index;
    }
}

#endif //SAXION_Y2Q1_CPP_COMPONENTPOOL_H
