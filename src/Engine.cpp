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

    _window.draw(_player.getDrawable());

    _window.display();
}

void Engine::update(float dt) {

//    sf::View view = _window.getView();
//    sf::Vector2f size = view.getSize();
//    size -= sf::Vector2f(20.0f, 10.0f) * dt;
//    view.setSize(size);
//    _window.setView(view);

    _player.update(dt);
}

Entity& Engine::makeEntity() {

    std::unique_ptr<Entity>& pEntity = _entities.emplace_back(new Entity);
    return *pEntity;
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
