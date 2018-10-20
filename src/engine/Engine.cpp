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

        render();
    }
}

void Engine::update(float dt) {

    for (auto& pComponent : m_components) {
        pComponent->update(dt);
    }
}

void Engine::render() {

    m_window.clear();

    for (auto& pComponent : m_components) {
        pComponent->draw(m_window);
    }

    m_window.display();
}

template<typename T>
inline void remove_from_vector(std::vector<std::shared_ptr<T>>& vec, const T* const item) {

    vec.erase(
        std::remove_if(
            vec.begin(),
            vec.end(),
            [&](const auto& p) { return p.get() == item; }
        ),
        vec.end()
    );
}

template<typename T>
inline void remove_from_vector(std::vector<T>& vec, const T& item) {

    vec.erase(
        std::remove(
            vec.begin(),
            vec.end(),
            item
        ),
        vec.end()
    );
}

void Engine::destroy(Entity& entity) {

    entity.destroy();

    Entity* const ptr = &entity;
    remove_from_vector(m_entities, ptr);
}

void Engine::registerComponent(std::shared_ptr<Component> pComponent) {
    m_components.push_back(pComponent);
}

void Engine::unregisterComponent(std::shared_ptr<Component> pComponent) {
    remove_from_vector(m_components, pComponent);
}

sf::RenderWindow& Engine::getWindow() { return m_window; }

std::shared_ptr<Entity> Engine::makeEntity() {

    auto pEntity = std::make_shared<Entity>(this);
    m_entities.push_back(pEntity);
    return pEntity;
}

std::shared_ptr<Entity> Engine::makeEntity(std::shared_ptr<Entity>& pParent) {

    auto pChild = makeEntity();
    return addChild(pParent, pChild);
}

std::shared_ptr<Entity>& Engine::addChild(std::shared_ptr<Entity>& pParent, std::shared_ptr<Entity>& pChild) {

    pParent->addChild(pChild);
    pChild->setParent(pParent);
    return pChild;
}

void Engine::removeChild(std::shared_ptr<Entity>& pParent, std::shared_ptr<Entity>& pChild) {

    pParent->removeChild(pChild);
    pChild->setParent({});
}