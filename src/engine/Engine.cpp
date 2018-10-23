//
// Created by Maksym Maisak on 27/9/18.
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Engine.h"
#include "Transformable.h"

#include <SFML/Graphics.hpp>

const sf::Time TIMESTEP = sf::seconds(0.01f);
const float TIMESTEP_SECONDS = TIMESTEP.asSeconds();

Engine* Engine::m_instance = nullptr;

Engine::Engine(unsigned int width, unsigned int height) {

    assert(!m_instance);

    m_instance = this;

    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 8;
    m_window.create(sf::VideoMode(width, height), "Example", sf::Style::Default, contextSettings);
}

Engine& Engine::getInstance() {

    assert(m_instance);
    return *m_instance;
}

void Engine::run() {

    sf::Clock clock;
    sf::Time lag = sf::Time::Zero;

    while (m_window.isOpen()) {

        lag += clock.restart();

        sf::Event event {};
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_window.close();
        }

        while (lag >= TIMESTEP) {
            update(TIMESTEP_SECONDS);
            lag -= TIMESTEP;
        }

        draw();
    }
}

void Engine::update(float dt) {

    for (auto& pSystem : m_systems) pSystem->update(dt);
    for (auto& pActor : m_actors) pActor->update(dt);
}

void Engine::draw() {

    m_window.clear();

    for (auto& pSystem : m_systems) pSystem->draw();
    for (auto& pActor : m_actors) pActor->draw();

    m_window.display();
}

Actor& Engine::makeActor() {

    return *m_actors.emplace_back(new Actor(*this, m_registry.makeEntity()));
}

void Engine::setParent(Entity child, std::optional<Entity> newParent) {

    auto& childTransformable = m_registry.get<en::Transformable>(child);

    if (childTransformable.m_parent.has_value()) {

        Entity oldParent = *childTransformable.m_parent;
        if (oldParent == newParent) return;
        m_registry.get<en::Transformable>(oldParent).removeChild(child);
    }

    if (newParent.has_value()) {

        auto& parentTransformable = m_registry.get<en::Transformable>(*newParent);
        parentTransformable.addChild(child);
    }

    childTransformable.m_parent = newParent;
    childTransformable.m_globalTransformNeedUpdate = true;
}
