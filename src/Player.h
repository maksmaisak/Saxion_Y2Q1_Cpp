//
// Created by Maksym Maisak on 27/9/18.
//

#ifndef SAXION_Y2Q1_CPP_PLAYER_H
#define SAXION_Y2Q1_CPP_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Update.h"

class Player : public Entity, public Update {

public:
    Player();
    void update(float dt);

protected:
    virtual void draw_self(sf::RenderTarget& renderTarget, const sf::Transform& transform) const;

private:

    sf::Vector2f _position;

    float _movementSpeed = 20.0f;

    sf::Texture _texture;
    sf::Sprite _sprite;
};

#endif //SAXION_Y2Q1_CPP_PLAYER_H
