//
// Created by Maksym Maisak on 4/10/18.
//

#include <iostream>
#include <algorithm>
#include "Entity.h"
#include "Engine.h"

Entity::~Entity() {

    std::cout << "~Entity" << std::endl;
}

void Entity::destroy() {

    assert(!_isDestroyed);

    _isDestroyed = true;
}

bool Entity::isDestroyed() const {return _isDestroyed; }
Entity* Entity::get_parent() const {return _parent; }

void Entity::addChild(std::shared_ptr<Entity>& pEntity) {

    assert(std::find(_children.cbegin(), _children.cend(), pEntity) == _children.cend());

    _children.push_back(pEntity);
    pEntity->_parent = this;
}

bool Entity::removeChild(const std::shared_ptr<Entity>& pEntity) {

    auto it = std::remove(
        _children.begin(),
        _children.end(),
        pEntity
    );

    auto end = _children.end();
    if (it == end) return false;

    _children.erase(it, end);
    pEntity->_parent = nullptr;
    return true;
}

sf::Transform Entity::getGlobalTransform() {

    if (!_parent) return getTransform();

    // TODO Cache this and keep track of invalidations.
    return _parent->getTransform() * getTransform();
}