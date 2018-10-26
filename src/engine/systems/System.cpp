//
// Created by Maksym Maisak on 22/10/18.
//

#include "System.h"
#include "Engine.h"

namespace en {

    System::System(Engine& engine) :
        m_engine(engine),
        m_registry(engine.getRegistry()) {}

    sf::RenderWindow& System::getWindow() {

        return m_engine.getWindow();
    }
}

