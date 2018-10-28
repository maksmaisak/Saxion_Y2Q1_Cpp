//
// Created by Maksym Maisak on 17/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COMPONENT_H
#define SAXION_Y2Q1_CPP_COMPONENT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntityRegistry.h"
#include "ActorDecl.h"

namespace en {

    // WARNING. Update functions are only guaranteed to be called if this component was added using Actor::add<TBehavior>()
    class Behavior {

    public:
        explicit Behavior(const Actor& actor);
        virtual ~Behavior() = default;

        inline Actor& actor() { return m_actor; }

        virtual void update(float dt) {};
        virtual void draw(sf::RenderTarget& renderTarget) {};

    protected:
        Actor m_actor;
        Engine* m_enginePtr;
        EntityRegistry* m_registryPtr;
    };
}

#endif //SAXION_Y2Q1_CPP_COMPONENT_H
