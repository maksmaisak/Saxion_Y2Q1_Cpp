//
// Created by Maksym Maisak on 21/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ACTOR_H
#define SAXION_Y2Q1_CPP_ACTOR_H

#include <vector>
#include "Engine.h"
#include "Behavior.h"

/// A thin wrapper around an entity that facilitates GameObject-like programming.
class Actor final {

public:
    Actor(Engine& engine) : m_engine(engine) {}

    virtual void update(float dt) {
        for (auto& pBehavior : m_behaviors) {
            pBehavior->update(dt);
        }
    };

    virtual void draw(sf::RenderTarget& renderTarget) {
        for (auto& pBehavior : m_behaviors) {
            pBehavior->draw(renderTarget);
        }
    };

    template<typename TBehavior, typename... Args>
    void add(Args&&... args) {
        m_behaviors.push_back(std::make_unique<TBehavior>(std::forward(args)...));
    }

private:
    Engine& m_engine;
    std::vector<std::unique_ptr<Behavior>> m_behaviors;
};


#endif //SAXION_Y2Q1_CPP_ACTOR_H
