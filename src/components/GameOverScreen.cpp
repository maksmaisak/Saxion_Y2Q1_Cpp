//
// Created by Maksym Maisak on 4/11/18.
//

#include "GameOverScreen.h"
#include <string>
#include <cstdint>
#include "State.h"

constexpr unsigned int CharacterSize = 100;

void GameOverScreen::start() {

    m_fontPtr = std::make_unique<sf::Font>();
    bool didLoadFont = m_fontPtr->loadFromFile("assets/hyperspace/Hyperspace.otf");
    assert(didLoadFont);

    addLine("GAME OVER");
    addLine("SCORE " + std::to_string(en::State::value<std::uint64_t, "score"_hs>()));
}

void GameOverScreen::update(float dt) {

    Behavior::update(dt);
}

void GameOverScreen::draw() {

    auto& window = m_engine->getWindow();

    const float lineSpacing = m_fontPtr->getLineSpacing(CharacterSize);
    const float offsetY = -lineSpacing * m_texts.size() * 0.5f;

    sf::Transform transform = {};
    transform.translate(window.getView().getCenter() + sf::Vector2f(0, offsetY));

    for (const auto& text : m_texts) {
        m_engine->getWindow().draw(text, transform);
    }
}

sf::Text& GameOverScreen::addLine(sf::String textString) {

    const float lineSpacing = m_fontPtr->getLineSpacing(CharacterSize);
    const float offsetY = lineSpacing * m_texts.size();

    auto& text = m_texts.emplace_back();
    text.setFont(*m_fontPtr);
    text.setCharacterSize(CharacterSize);
    text.setString(textString);
    text.setPosition(sf::Vector2f(0, offsetY));

    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2, 0.f);

    return text;
}
