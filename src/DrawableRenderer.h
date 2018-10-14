//
// Created by Maksym Maisak on 14/10/18.
//

#ifndef SAXION_Y2Q1_CPP_DRAWABLERENDERER_H
#define SAXION_Y2Q1_CPP_DRAWABLERENDERER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EngineCallbacks.h"

class DrawableRenderer : public Entity, public Draw {

public:
    DrawableRenderer(std::shared_ptr<sf::Drawable> drawable);
    void draw(sf::RenderTarget& renderTarget);

private:
    std::shared_ptr<sf::Drawable> m_drawable;
};


#endif //SAXION_Y2Q1_CPP_DRAWABLERENDERER_H
