//
// Created by Maksym Maisak on 5/10/18.
//

#ifndef SAXION_Y2Q1_CPP_SPRITERENDERER_H
#define SAXION_Y2Q1_CPP_SPRITERENDERER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EngineCallbacks.h"

class SpriteRenderer : public Entity, public Draw {

public:
    SpriteRenderer(const std::string& filePath);
    void draw(sf::RenderTarget& renderTarget);

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};


#endif //SAXION_Y2Q1_CPP_SPRITERENDERER_H
