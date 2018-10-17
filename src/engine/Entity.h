//
// Created by Maksym Maisak on 4/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITY_H
#define SAXION_Y2Q1_CPP_ENTITY_H

#include <vector>
#include <SFML/Graphics.hpp>

class Entity : public sf::Transformable {

public:
    Entity();
    ~Entity();

    bool isDestroyed() const;
    sf::Transform getGlobalTransform() const;
    std::weak_ptr<Entity> getParent() const;

private:

    std::weak_ptr<Entity> m_parent;
    std::vector<std::shared_ptr<Entity>> m_children;
    bool m_isDestroyed = false;

    void addChild(const std::shared_ptr<Entity>& pEntity);
    bool removeChild(const std::shared_ptr<Entity>& pEntity);

    void setParent(const std::shared_ptr<Entity>& pEntity);
    void removeParent();

    void destroy();
    friend class Engine;
};


#endif //SAXION_Y2Q1_CPP_ENTITY_H
