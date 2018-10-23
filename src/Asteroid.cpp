//
// Created by Maksym Maisak on 18/10/18.
//

#include "Asteroid.h"
#include "DrawableRenderer.h"
#include "MyMath.h"

void Asteroid::update(float dt) {

    m_velocity += en::randomInCircle(32.f) * dt;
    //getEntity().move(m_velocity * dt);

    //flicker();
}

void Asteroid::flicker() {

    /*
    auto pRenderer = m_engine.getRegistry().get<DrawableRenderer>(m_Entity);
    if (!pRenderer) return;

    auto pDrawable = pRenderer->getDrawable();
    if (!pDrawable) return;

    auto pShape = dynamic_cast<sf::Shape*>(pDrawable.get());
    pShape->setOutlineThickness(en::random(1.f, 2.f));
     */
}
