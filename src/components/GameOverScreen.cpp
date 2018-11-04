//
// Created by Maksym Maisak on 4/11/18.
//

#include "GameOverScreen.h"
#include <string>
#include <cstdint>
#include "State.h"

void GameOverScreen::start() {

    m_fontPtr = std::make_unique<sf::Font>();
    bool didLoadFont = m_fontPtr->loadFromFile("assets/hyperspace/Hyperspace.otf");
    assert(didLoadFont);

    m_text = std::make_unique<sf::Text>();
    m_text->setFont(*m_fontPtr);
    m_text->setCharacterSize(100);
    m_text->setString("GAME OVER\nSCORE " + std::to_string(en::State::value<std::uint64_t, "score"_hs>()));
    m_text->setPosition(m_engine->getWindow().getView().getCenter());

    auto bounds = m_text->getLocalBounds();
    m_text->setOrigin(bounds.width / 2, bounds.height / 2);
}

void GameOverScreen::update(float dt) {

    Behavior::update(dt);
}

void GameOverScreen::draw() {

    m_engine->getWindow().draw(*m_text);
}
