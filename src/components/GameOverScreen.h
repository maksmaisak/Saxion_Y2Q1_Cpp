//
// Created by Maksym Maisak on 4/11/18.
//

#ifndef SAXION_Y2Q1_CPP_GAMEOVERSCREEN_H
#define SAXION_Y2Q1_CPP_GAMEOVERSCREEN_H

#include "Engine.h"
#include "Behavior.h"

class GameOverScreen : public en::Behavior {

    using Behavior::Behavior;

public:
    void start() override;
    void update(float dt) override;
    void draw() override;

private:
    std::unique_ptr<sf::Font> m_fontPtr;
    std::unique_ptr<sf::Text> m_text;
};

#endif //SAXION_Y2Q1_CPP_GAMEOVERSCREEN_H
