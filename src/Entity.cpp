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

    Engine::getInstance().remove(this);
}

bool Entity::isDestroyed() const {

    return _isDestroyed;
}

void Entity::addChild(std::shared_ptr<Entity>& pEntity) {

    assert(std::find(_children.cbegin(), _children.cend(), pEntity) == _children.cend());

    _children.push_back(pEntity);
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
    return true;
}

void Entity::draw(sf::RenderTarget& renderTarget) const {

    draw(renderTarget, sf::Transform::Identity);
}

void Entity::draw(sf::RenderTarget& renderTarget, const sf::Transform& parentTransform) const {

    sf::Transform combinedTransform = parentTransform * getTransform();

    draw_self(renderTarget, combinedTransform);

    for (const std::shared_ptr<Entity>& pChild : _children) {

        assert(!pChild->isDestroyed());

        pChild->draw(renderTarget, combinedTransform);
    }
}
