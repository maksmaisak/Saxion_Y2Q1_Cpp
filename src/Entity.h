//
// Created by Maksym Maisak on 4/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITY_H
#define SAXION_Y2Q1_CPP_ENTITY_H

#include <vector>
#include <SFML/Graphics.hpp>

class Entity : public sf::Transformable {

public:
    ~Entity();

    bool isDestroyed() const;
    Entity* get_parent() const;

    // TODO Make "addChild<T>(args...)" in place, similar to makeEntity, to avoid godawful pointer casting.

    void addChild(std::shared_ptr<Entity>& pEntity);
    bool removeChild(const std::shared_ptr<Entity>& pEntity);

    sf::Transform getGlobalTransform();

private:

    Entity* _parent;
    std::vector<std::shared_ptr<Entity>> _children;
    bool _isDestroyed = false;

    void destroy();
    friend class Engine;
};


#endif //SAXION_Y2Q1_CPP_ENTITY_H
