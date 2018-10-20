//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <typeindex>
#include <iostream>
#include "Component.h"

class Entity;

template<typename... TComponent>
class EntitiesView;

class Engine {

public:
    Engine(unsigned int width, unsigned int height);
    virtual ~Engine() = default;

    static Engine& getInstance();
    void run();

    std::shared_ptr<Entity> makeEntity();
    std::shared_ptr<Entity> makeEntity(std::shared_ptr<Entity>& pParent);

    template<typename... TComponent>
    EntitiesView<TComponent...> with();

    /// Returns the shared_ptr to the child to allow call chaining.
    std::shared_ptr<Entity>& addChild(std::shared_ptr<Entity>& pParent, std::shared_ptr<Entity>& pChild);
    void removeChild(std::shared_ptr<Entity>& pParent, std::shared_ptr<Entity>& pChild);

    void registerComponent(std::shared_ptr<Component> pComponent);
    void unregisterComponent(std::shared_ptr<Component> component);

    void destroy(Entity& entity);
    sf::RenderWindow& getWindow();

private:

    static Engine* m_instance;

    sf::RenderWindow m_window;
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<Component>> m_components;

    void render();
    void update(float dt);
};

class Entity final : public sf::Transformable {

public:
    explicit Entity(Engine* pEngine);
    ~Entity() final;

    Engine* getEngine() const;

    bool isDestroyed() const;
    sf::Transform getGlobalTransform() const;
    std::weak_ptr<Entity> getParent() const;

    template<class T>
    std::shared_ptr<T> get();

    template<class T, typename... Args>
    std::shared_ptr<T> add(Args&&... args);

private:

    Engine* const m_pEngine;

    std::weak_ptr<Entity> m_parent;
    std::vector<std::shared_ptr<Entity>> m_children;
    bool m_isDestroyed = false;

    std::map<std::type_index, std::shared_ptr<Component>> m_components;

    void addChild(const std::shared_ptr<Entity>& pEntity);
    bool removeChild(const std::shared_ptr<Entity>& pEntity);
    void setParent(const std::weak_ptr<Entity>& pEntity);

    void destroy();
    friend class Engine;
};

template<typename... TComponent>
class EntitiesView {

    using underlyingCollection_type = std::vector<std::shared_ptr<Entity>>;
    using underlyingIterator_type = underlyingCollection_type::iterator;

    class iterator {

    public:

        // Typedefs required to qualify as Iterator.
        using difference_type   = underlyingIterator_type::difference_type;
        using value_type        = underlyingIterator_type::value_type;
        using pointer           = underlyingIterator_type::pointer;
        using reference         = underlyingIterator_type::reference;
        using iterator_category = std::forward_iterator_tag;

        explicit iterator(underlyingIterator_type underlyingIterator, underlyingIterator_type end)
            : m_underlyingIterator(underlyingIterator), m_end(end) {}

        inline reference operator  *() const {return m_underlyingIterator.operator*();}
        inline pointer   operator ->() const {return m_underlyingIterator.operator->();}

        inline bool operator ==(const iterator& other) {return m_underlyingIterator == other.m_underlyingIterator;}
        inline bool operator !=(const iterator& other) {return m_underlyingIterator != other.m_underlyingIterator;}

        inline iterator& operator ++() {

            while (m_underlyingIterator != m_end && (m_underlyingIterator->get()->get<TComponent>() && ...)) {
                ++m_underlyingIterator;
            }
            return *this;
        }

    private:
        underlyingIterator_type m_underlyingIterator;
        underlyingIterator_type m_end;
    };

public:

    EntitiesView(underlyingCollection_type& entities) : m_entities(entities) {}

    inline iterator begin() {
        return iterator(m_entities.begin(), m_entities.end());
    }

    inline iterator end() {
        return iterator(m_entities.end()  , m_entities.end());
    }

private:

    underlyingCollection_type& m_entities;
};

template<typename... TComponent>
EntitiesView<TComponent...> Engine::with() {
    return EntitiesView<TComponent...>(m_entities);
}

template<class T>
inline std::type_index getTypeIndex() {
    return std::type_index(typeid(T));
}

template<typename T, typename Base>
inline constexpr bool inherits = std::is_base_of<Base, T>::value;

template<class T>
std::shared_ptr<T> Entity::get() {

    static_assert(inherits<T, Component>);

    auto it = m_components.find(getTypeIndex<T>());
    if (it == m_components.end()) return std::shared_ptr<T>();

    return std::static_pointer_cast<T>(it->second);
}

template<class T, typename... Args>
std::shared_ptr<T> Entity::add(Args&&... args) {

    static_assert(inherits<T, Component>);

    const std::type_index index = getTypeIndex<T>();
    assert(m_components.count(index) == 0);

    std::shared_ptr<T> pComponent = std::make_shared<T>(this, std::forward<Args>(args)...);
    m_components.emplace(index, pComponent);
    m_pEngine->registerComponent(pComponent);

    return pComponent;
}

#endif //SAXION_Y2Q1_CPP_ENGINE_H
