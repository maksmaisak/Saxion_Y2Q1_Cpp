//
// Created by Maksym Maisak on 3/11/18.
//

#include "ScoreSystem.h"
#include <string>
#include <cstdint>
#include "State.h"

void setOriginNormalized(sf::Text& text, sf::Vector2f coords = {0.5f, 0.5f}) {

    sf::Rect bounds = text.getLocalBounds();
    text.setOrigin({bounds.width * coords.x, bounds.height * coords.y});
}

void ScoreSystem::start() {

    m_fontPtr = std::make_unique<sf::Font>();
    bool didLoadFont = m_fontPtr->loadFromFile("assets/hyperspace/Hyperspace.otf");
    assert(didLoadFont);

    m_scoreTextPtr = std::make_unique<sf::Text>();
    m_scoreTextPtr->setFont(*m_fontPtr);

    m_scoreTextPtr->setCharacterSize(72);

    const sf::View& view = m_engine->getWindow().getView();
    const sf::Vector2f size = view.getSize();
    const sf::Vector2f position = view.getCenter() + sf::Vector2f(size.x * 0.5f, -size.y * 0.5f);
    m_scoreTextPtr->setPosition(position);
}

void ScoreSystem::draw() {

    m_scoreTextPtr->setString("Score " + std::to_string(en::State::value<std::uint64_t, "score"_hs>()));
    setOriginNormalized(*m_scoreTextPtr, {1, 0});
    m_engine->getWindow().draw(*m_scoreTextPtr);
}

void ScoreSystem::receive(const en::ComponentWillBeRemoved<Asteroid>& info) {

    en::State::value<std::uint64_t, "score"_hs>() += 100;
}

void ScoreSystem::receive(const Restart& info) {

    en::State::value<std::uint64_t, "score"_hs>() = 0;
}
