//
// Created by Maksym Maisak on 21/10/18.
//

#include "Actor.h"
#include "Engine.h"

Actor::Actor(Engine& engine, Entity entity) :
    m_engine(engine),
    m_registry(engine.getRegistry()),
    m_entity(entity)
    {}

void Actor::update(float dt) {
    for (auto& pBehavior : m_behaviors) pBehavior->update(dt);
}

void Actor::draw() {
    for (auto& pBehavior : m_behaviors) pBehavior->draw(m_engine.getWindow());
}
