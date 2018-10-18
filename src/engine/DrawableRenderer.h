//
// Created by Maksym Maisak on 14/10/18.
//

#ifndef SAXION_Y2Q1_CPP_DRAWABLERENDERER_H
#define SAXION_Y2Q1_CPP_DRAWABLERENDERER_H

#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Component.h"
#include "EngineCallbacks.h"

class DrawableRenderer : public Component, public Draw {

public:
    DrawableRenderer(Entity* pEntity, std::shared_ptr<sf::Drawable> drawable);
    void draw(sf::RenderTarget& renderTarget) final;

private:
    std::shared_ptr<sf::Drawable> m_drawable;
};


#endif //SAXION_Y2Q1_CPP_DRAWABLERENDERER_H
