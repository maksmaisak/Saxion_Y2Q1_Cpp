//
// Created by Maksym Maisak on 27/10/18.
//

#include "DiagnosticsSystem.h"
#include "GameTime.h"
#include "Engine.h"

DiagnosticsSystem::DiagnosticsSystem(en::Engine& engine) : System(engine) {

    m_fontPtr = std::make_unique<sf::Font>();
    m_fontPtr->loadFromFile("assets/Menlo.ttc");

    m_fpsCounterPtr = std::make_unique<sf::Text>();
    m_fpsCounterPtr->setFont(*m_fontPtr);
}

void DiagnosticsSystem::draw() {

    sf::Time frameTime = m_timer.restart();

    m_fpsCounterPtr->setString("fps: " + std::to_string(1.f / frameTime.asSeconds()));

    m_engine.getWindow().draw(*m_fpsCounterPtr);
}
