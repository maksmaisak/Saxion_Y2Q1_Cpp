//
// Created by Maksym Maisak on 27/9/18.
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Engine.h"

Engine Engine::_instance = Engine();

Engine::Engine() {

    _window.create(sf::VideoMode(1280, 1024), "Example");
}

Engine& Engine::getInstance() {

    return _instance;
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

void Engine::render() {

    _window.clear();

    for (const std::shared_ptr<Entity>& pEntity : _entities)
    {
        assert(!pEntity->isDestroyed());
        pEntity->draw(_window);
    }

    _window.display();
}

void Engine::update(float dt) {

//    sf::View view = _window.getView();
//    sf::Vector2f size = view.getSize();
//    size -= sf::Vector2f(20.0f, 10.0f) * dt;
//    view.setSize(size);
//    _window.setView(view);

    for (const std::shared_ptr<Entity>& pEntity : _entities)
    {
        assert(!pEntity->isDestroyed());
        pEntity->update(dt);
    }
}

void Engine::remove(Entity* pEntity) {

    _entities.erase(
        std::remove_if(
            _entities.begin(),
            _entities.end(),
            [&](const auto& p) { return p.get() == pEntity; }
        ),
        _entities.end()
    );
}
