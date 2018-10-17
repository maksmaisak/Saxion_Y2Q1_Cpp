//
// Created by Maksym Maisak on 4/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENGINECALLBACKS_H
#define SAXION_Y2Q1_CPP_ENGINECALLBACKS_H

#include <SFML/Graphics.hpp>

class Update {
public:
    virtual void update(float dt) = 0;
};

class Draw {
public:
    virtual void draw(sf::RenderTarget& renderTarget) = 0;
};

#endif //SAXION_Y2Q1_CPP_ENGINECALLBACKS_H
