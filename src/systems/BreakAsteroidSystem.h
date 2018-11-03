//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_BREAKASTEROIDSYSTEM_H
#define SAXION_Y2Q1_CPP_BREAKASTEROIDSYSTEM_H

#include <vector>
#include "Engine.h"
#include "Messaging.h"
#include "Collision.h"

class BreakAsteroidSystem : public en::System, en::Receiver<en::Collision> {

public:
    void update(float dt) override;

private:
    std::vector<en::Entity> m_entitiesToDestroy;

    void receive(const en::Collision& info) override;
};


#endif //SAXION_Y2Q1_CPP_BREAKASTEROIDSYSTEM_H
