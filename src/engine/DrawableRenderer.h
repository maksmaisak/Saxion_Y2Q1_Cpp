//
// Created by Maksym Maisak on 14/10/18.
//

#ifndef SAXION_Y2Q1_CPP_DRAWABLERENDERER_H
#define SAXION_Y2Q1_CPP_DRAWABLERENDERER_H

#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Component.h"

class DrawableRenderer : public Component {

public:
    DrawableRenderer(Entity* pEntity, std::shared_ptr<sf::Drawable> drawable);
    void draw(sf::RenderTarget& renderTarget) override;
    const std::shared_ptr<sf::Drawable>& getDrawable() const;

private:
    std::shared_ptr<sf::Drawable> m_drawable;
};

#endif //SAXION_Y2Q1_CPP_DRAWABLERENDERER_H
