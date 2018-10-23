//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITIESVIEW_H
#define SAXION_Y2Q1_CPP_ENTITIESVIEW_H

#include <algorithm>
#include <set>
#include <tuple>
#include "Entity.h"
#include "engine/ecs/ComponentPool.h"

template<typename... TComponent>
class EntitiesView {

    using underlyingCollection_type = std::set<Entity>;
    using underlyingIterator_type = underlyingCollection_type::iterator;

    class iterator {

        inline bool shouldSkip() {
            return !(std::get<ComponentPool<TComponent>&>(m_pools).count(*m_underlyingIterator) && ...); //!(m_registry.get<TComponent>(*m_underlyingIterator) && ...);
        }

    public:

        // Typedefs required to qualify as an Iterator.
        using difference_type   = underlyingIterator_type::difference_type;
        using value_type        = underlyingIterator_type::value_type;
        using pointer           = underlyingIterator_type::pointer;
        using reference         = underlyingIterator_type::reference;
        using iterator_category = std::forward_iterator_tag;

        iterator(std::tuple<ComponentPool<TComponent>&...> pools, underlyingIterator_type underlyingIterator, underlyingIterator_type end)
            : m_pools(pools), m_underlyingIterator(underlyingIterator), m_end(end) {

            if (m_underlyingIterator != m_end && shouldSkip()) {
                ++(*this);
            }
        }

        inline reference operator  *() const {return m_underlyingIterator.operator *();}
        inline pointer   operator ->() const {return m_underlyingIterator.operator->();}

        inline bool operator ==(const iterator& other) {return m_underlyingIterator == other.m_underlyingIterator;}
        inline bool operator !=(const iterator& other) {return m_underlyingIterator != other.m_underlyingIterator;}

        inline iterator& operator ++() {

            do ++m_underlyingIterator;
            while (m_underlyingIterator != m_end && shouldSkip());

            return *this;
        }

    private:

        std::tuple<ComponentPool<TComponent>&...> m_pools;
        underlyingIterator_type m_underlyingIterator;
        underlyingIterator_type m_end;
    };

public:

    EntitiesView(underlyingCollection_type& entities, ComponentPool<TComponent>&... pools) : m_entities(entities), m_pools{pools...} {}

    inline iterator begin() {
        return iterator(m_pools, m_entities.cbegin(), m_entities.cend());
    }

    inline iterator end() {
        return iterator(m_pools, m_entities.cend()  , m_entities.cend());
    }

private:

    std::tuple<ComponentPool<TComponent>&...> m_pools;

    const underlyingCollection_type& m_entities;
};

#endif //SAXION_Y2Q1_CPP_ENTITIESVIEW_H
