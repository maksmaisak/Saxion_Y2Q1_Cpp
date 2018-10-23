//
// Created by Maksym Maisak on 21/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ACTOR_H
#define SAXION_Y2Q1_CPP_ACTOR_H

#include <memory>
#include <vector>
#include <type_traits>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Behavior.h"

class Engine;

template<typename T>
constexpr inline bool isBehavior = std::is_base_of<Behavior, T>::value;

/// A thin wrapper around an entity. Facilitates GameObject-like programming.
class Actor final {

public:
    Actor(Engine& engine, Entity entity);
    ~Actor() = default;
    Actor(const Actor& other) = delete;
    Actor& operator=(const Actor& rhs) = delete;
    Actor(const Actor&& other) = delete;
    Actor& operator=(const Actor&& rhs) = delete;

    virtual void update(float dt);
    void draw();

    /// Adds a behavior component.
    template<typename TBehavior, typename... Args>
    std::enable_if_t<isBehavior<TBehavior>, TBehavior&>
    add(Actor& actor, Args&&... args);

    /// Adds a behavior component with the first parameter (actor) being omitted.
    template<typename TBehavior, typename... Args>
    inline std::enable_if_t<isBehavior<TBehavior>, TBehavior&>
    add(Args&&... args);

    /// Adds a non-behavior component
    template<typename TComponent, typename... Args>
    std::enable_if_t<!isBehavior<TComponent>, TComponent&>
    add(Args&&... args);

    inline Engine& getEngine() {return m_engine;}
    inline operator Entity() {return m_entity;}

private:
    Engine& m_engine;
    EntityRegistry& m_registry;
    const Entity m_entity;
    std::vector<std::unique_ptr<Behavior>> m_behaviors;
};

template<typename TBehavior, typename... Args>
std::enable_if_t<isBehavior<TBehavior>, TBehavior&>
Actor::add(Actor& actor, Args&&... args) {

    assert(&actor == this);

    std::unique_ptr<TBehavior> ptr = std::make_unique<TBehavior>(actor, std::forward<Args>(args)...);
    TBehavior& behavior = *ptr;
    m_behaviors.push_back(std::move(ptr));
    return behavior;
}

template<typename TBehavior, typename... Args>
std::enable_if_t<isBehavior<TBehavior>, TBehavior&>
Actor::add(Args&&... args) { return add<TBehavior>(*this, std::forward<Args>(args)...); }

template<typename TComponent, typename... Args>
std::enable_if_t<!isBehavior<TComponent>, TComponent&>
Actor::add(Args&&... args) {
    return m_registry.add<TComponent>(m_entity, std::forward<Args>(args)...);
}


#endif //SAXION_Y2Q1_CPP_ACTOR_H
