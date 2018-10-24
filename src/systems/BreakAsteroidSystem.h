//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_BREAKASTEROIDSYSTEM_H
#define SAXION_Y2Q1_CPP_BREAKASTEROIDSYSTEM_H

#include "Engine.h"
#include "Messaging.h"
#include "Collision.h"

class BreakAsteroidSystem : public System, Receiver<en::Collision> {

    using System::System;

    void receive(const en::Collision& info) override;
};


#endif //SAXION_Y2Q1_CPP_BREAKASTEROIDSYSTEM_H
