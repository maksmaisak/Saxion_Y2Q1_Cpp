//
// Created by Maksym Maisak on 27/9/18.
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Engine.h"

const sf::Time TIMESTEP = sf::seconds(0.01f);
const float TIMESTEP_SECONDS = TIMESTEP.asSeconds();

Engine* Engine::m_instance = nullptr;

Engine::Engine(unsigned int width, unsigned int height) {

    assert(!m_instance);

    m_instance = this;

    m_window.create(sf::VideoMode(width, height), "Example");
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

        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_window.close();
        }

        while (lag >= TIMESTEP) {
            update(TIMESTEP_SECONDS);
            lag -= TIMESTEP;
        }

        render();
    }
}

void Engine::update(float dt) {

    for (const std::shared_ptr<Entity>& pEntity : m_update) {
        assert(!pEntity->isDestroyed());
        dynamic_cast<Update*>(pEntity.get())->update(dt);
    }
}

void Engine::render() {

    m_window.clear();

    for (const std::shared_ptr<Entity>& pEntity : m_draw) {
        assert(!pEntity->isDestroyed());
        dynamic_cast<Draw*>(pEntity.get())->draw(m_window);
    }

    m_window.display();
}

template<typename T>
void remove_from_vector(std::vector<std::shared_ptr<T>>& vec, const T* const item) {

    vec.erase(
        std::remove_if(
            vec.begin(),
            vec.end(),
            [&](const auto& p) { return p.get() == item; }
        ),
        vec.end()
    );
}

void Engine::destroy(Entity& entity) {

    entity.destroy();

    Entity* const ptr = &entity;
    remove_from_vector(m_entities, ptr);
    remove_from_vector(m_update, ptr);
    remove_from_vector(m_draw, ptr);
}

sf::RenderWindow& Engine::getWindow() { return m_window; }
