//
// Created by Maksym Maisak on 27/9/18.
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Engine.h"

Engine* Engine::_instance = nullptr;

Engine::Engine(unsigned int width, unsigned int height) {

    assert(!_instance);

    _instance = this;

    _window.create(sf::VideoMode(width, height), "Example");
}

Engine& Engine::getInstance() {

    assert(_instance);

    return *_instance;
}

void Engine::run() {

    sf::Clock clock;

    while (_window.isOpen()) {

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) _window.close();
        }

        update(0.01f);
        render();
    }
}

void Engine::update(float dt) {

    for (const std::shared_ptr<Entity>& pEntity : _update)
    {
        assert(!pEntity->isDestroyed());
        dynamic_cast<Update*>(pEntity.get())->update(dt);
    }
}

void Engine::render() {

    _window.clear();

    for (const std::shared_ptr<Entity>& pEntity : _draw)
    {
        assert(!pEntity->isDestroyed());
        dynamic_cast<Draw*>(pEntity.get())->draw(_window);
    }

    _window.display();
}

template<typename T>
void remove_from_vector(std::vector<std::shared_ptr<T>>& vec, T* item) {

    vec.erase(
        std::remove_if(
            vec.begin(),
            vec.end(),
            [&](const auto& p) { return p.get() == item; }
        ),
        vec.end()
    );
}

void Engine::destroy(Entity* pEntity) {

    pEntity->destroy();

    remove_from_vector(_entities, pEntity);
    remove_from_vector(_update, pEntity);
    remove_from_vector(_draw, pEntity);
}

sf::RenderWindow& Engine::getWindow() {return _window; }
