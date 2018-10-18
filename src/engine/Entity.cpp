//
// Created by Maksym Maisak on 4/10/18.
//

#include <iostream>
#include <algorithm>
#include "Engine.h"

Entity::Entity(Engine* pEngine) : m_pEngine(pEngine) {

    setOrigin(0.5f, 0.5f);
}

Entity::~Entity() {

    std::cout << "~Entity" << std::endl;
}

sf::Transform Entity::getGlobalTransform() const {

    auto pParent = m_parent.lock();
    if (!pParent) return getTransform();

    // TODO Cache this and keep track of invalidations.
    return pParent->getGlobalTransform() * getTransform();
}

std::weak_ptr<Entity> Entity::getParent() const {

    return m_parent;
}

bool Entity::isDestroyed() const {

    return m_isDestroyed;
}

void Entity::destroy() {

    assert(!m_isDestroyed);

    m_isDestroyed = true;
}

void Entity::addChild(const std::shared_ptr<Entity>& pEntity) {

    assert(std::find(m_children.cbegin(), m_children.cend(), pEntity) == m_children.cend());

    m_children.push_back(pEntity);
}

bool Entity::removeChild(const std::shared_ptr<Entity>& pEntity) {

    auto it = std::remove(
        m_children.begin(),
        m_children.end(),
        pEntity
    );

    auto end = m_children.end();
    if (it == end) return false;

    m_children.erase(it, end);
    return true;
}

void Entity::setParent(const std::weak_ptr<Entity>& pEntity) {
    m_parent = pEntity;
}