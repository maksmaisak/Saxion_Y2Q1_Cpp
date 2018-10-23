//
// Created by Maksym Maisak on 23/10/18.
//

#ifndef SAXION_Y2Q1_CPP_FLICKER_H
#define SAXION_Y2Q1_CPP_FLICKER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "MyMath.h"

struct Flicker {
    std::shared_ptr<sf::Shape> m_shape;
};

class FlickerSystem : public System {

    using System::System;
public:

    void update(float dt) override {

        for (Entity e : m_registry.with<Flicker>()) {

            m_registry.get<Flicker>(e).m_shape->setOutlineThickness(en::random(1.f, 4.f));
        }
    }
}

#endif //SAXION_Y2Q1_CPP_FLICKER_H
