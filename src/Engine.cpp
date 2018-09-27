//
// Created by Maksym Maisak on 27/9/18.
//
#include <iostream>
#include <cmath>
#include "Engine.h"

Engine::Engine() {

    _window.create(sf::VideoMode(1280, 1024), "Example");
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

    sf::View view = _window.getView();
    sf::Vector2f size = view.getSize();
    size -= sf::Vector2f(20.0f, 10.0f) * dt;
    view.setSize(size);
    _window.setView(view);

    _player.update(dt);
}
