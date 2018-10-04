//
// Created by Maksym Maisak on 4/10/18.
//

#include <iostream>
#include "Entity.h"
#include "Engine.h"

Entity::~Entity() {

    std::cout << "~Entity" << std::endl;
}

void Entity::destroy() {

    assert(!_isDestroyed);

    Engine::getInstance().remove(this);
}

bool Entity::isDestroyed() {

    return _isDestroyed;
}
