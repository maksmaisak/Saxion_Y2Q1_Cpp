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

    void destroy();

    bool isDestroyed() const;

    void addChild(std::shared_ptr<Entity>& pEntity);

    bool removeChild(const std::shared_ptr<Entity>& pEntity);

    void draw(sf::RenderTarget& renderTarget) const;

protected:
    virtual void draw_self(sf::RenderTarget& renderTarget, const sf::Transform& transform) const {}

private:
    void draw(sf::RenderTarget& renderTarget, const sf::Transform& parentTransform) const;

    bool _isDestroyed = false;
    std::vector<std::shared_ptr<Entity>> _children;
};


#endif //SAXION_Y2Q1_CPP_ENTITY_H
