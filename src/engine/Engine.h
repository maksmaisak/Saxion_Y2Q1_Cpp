//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINE_H
#define SAXION_Y2Q1_CPP_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <optional>
#include <typeindex>
#include <type_traits>
#include <iostream>
#include "EntityRegistry.h"
#include "Entity.h"
#include "System.h"
#include "BehaviorSystem.h"

namespace en {

    class Behavior;
    class Actor;

    class Engine final {

    public:
        Engine(unsigned int width, unsigned int height, bool enableVsync = false);

        void run();

        inline EntityRegistry& getRegistry() { return m_registry; }

        inline sf::RenderWindow& getWindow() { return m_window; }

        static Engine& getInstance();

        Actor makeActor();

        template<typename TSystem, typename... Args>
        TSystem& addSystem(Engine& engine, Args&& ... args);

        /// A convenience function which lets you omit passing Engine& to the constructor
        template<typename TSystem, typename... Args>
        TSystem& addSystem(Args&& ... args);

        /// Makes sure a system to handle a given behavior type is in place.
        template<typename TBehavior>
        bool ensureBehaviorSystem();

        void setParent(Entity child, std::optional<Entity> newParent);

    private:

        static Engine* m_instance;

        EntityRegistry m_registry;
        sf::RenderWindow m_window;

        std::vector<std::unique_ptr<System>> m_systems;
        std::set<std::type_index> m_behaviorSystems;

        void draw();

        void update(float dt);
    };

    template<typename TSystem, typename... Args>
    TSystem& Engine::addSystem(Engine& engine, Args&& ... args) {

        assert(&engine == this);

        std::unique_ptr<TSystem> ptr = std::make_unique<TSystem>(engine, std::forward<Args>(args)...);
        TSystem& system = *ptr;
        m_systems.push_back(std::move(ptr));
        return system;
    }

    template<typename TSystem, typename... Args>
    TSystem& Engine::addSystem(Args&& ... args) {

        return addSystem<TSystem>(*this, std::forward(args)...);
    }

    template<typename TBehavior>
    bool Engine::ensureBehaviorSystem() {

        static_assert(std::is_base_of_v<Behavior, TBehavior>);

        auto typeIndex = std::type_index(typeid(TBehavior));
        if (m_behaviorSystems.find(typeIndex) == m_behaviorSystems.end()) {

            addSystem<BehaviorSystem<TBehavior>>();
            m_behaviorSystems.insert(typeIndex);
            return true;
        }

        return false;
    }
}

#endif //SAXION_Y2Q1_CPP_ENGINE_H
