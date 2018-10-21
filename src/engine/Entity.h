//
// Created by Maksym Maisak on 21/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITY_H
#define SAXION_Y2Q1_CPP_ENTITY_H

#include <SFML/Graphics.hpp>
#include <typeindex>

class Engine;
class Component;

class Entity final : public sf::Transformable {

    friend class Engine;

public:
    explicit Entity(Engine* pEngine);
    ~Entity() final;

    Engine* getEngine() const;

    bool isDestroyed() const;
    sf::Transform getGlobalTransform() const;
    std::weak_ptr<Entity> getParent() const;

private:

    Engine* const m_pEngine;

    std::weak_ptr<Entity> m_parent;
    std::vector<std::shared_ptr<Entity>> m_children;
    bool m_isDestroyed = false;

    std::map<std::type_index, std::shared_ptr<Component>> m_components;

    void addChild(const std::shared_ptr<Entity>& pEntity);
    bool removeChild(const std::shared_ptr<Entity>& pEntity);
    void setParent(const std::weak_ptr<Entity>& pEntity);

    void destroy();
    friend class Engine;
};

#endif //SAXION_Y2Q1_CPP_ENTITY_H
