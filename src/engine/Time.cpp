//
// Created by Maksym Maisak on 14/10/18.
//

#include "Time.h"

const sf::Clock Time::m_clock;

sf::Time Time::now() {
    return m_clock.getElapsedTime();
}