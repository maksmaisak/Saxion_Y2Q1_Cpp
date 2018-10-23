//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_TRANSFORM_H
#define SAXION_Y2Q1_CPP_TRANSFORM_H

#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>
#include "EntityRegistry.h"

namespace components {

    /// TODO make this an exact copy of sf::Transformable, but with hierarchy-preserving functionality.
    class Transform final {

    public:

        Transformable();
        Transformable(EntityRegistry* registry) : m_registry(registry) {}

        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& position);
        void setRotation(float angle);
        void setScale(float factorX, float factorY);
        void setScale(const sf::Vector2f& factors);
        void setOrigin(float x, float y);
        void setOrigin(const sf::Vector2f& origin);
        const sf::Vector2f& getPosition() const;
        float getRotation() const;
        const sf::Vector2f& getScale() const;
        const sf::Vector2f& getOrigin() const;
        void move(float offsetX, float offsetY);
        void move(const sf::Vector2f& offset);
        void rotate(float angle);
        void scale(float factorX, float factorY);
        void scale(const sf::Vector2f& factor);
        const sf::Transform& getTransform() const;

        const sf::Transform& getGlobalTransform() {

            if (m_isDirty || m_local.isDirty) {}
        }

    private:

        sf::Transformable m_local;

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::Vector2f          m_origin;                     ///< Origin of translation/rotation/scaling of the object
        sf::Vector2f          m_position;                   ///< Position of the object in the 2D world
        float                 m_rotation;                   ///< Orientation of the object, in degrees
        sf::Vector2f          m_scale;                      ///< Scale of the object
        mutable sf::Transform m_transform;                  ///< Combined transformation of the object
        mutable bool          m_transformNeedUpdate;        ///< Does the transform need to be recomputed?
        mutable sf::Transform m_inverseTransform;           ///< Combined transformation of the object
        mutable bool          m_inverseTransformNeedUpdate; ///< Does the transform need to be recomputed?

    public:

    private:
        EntityRegistry* m_registry;
        std::optional<Entity> m_parent;
        std::vector<Entity> m_children;
        bool m_isDirty = false;

        inline void makeDirty() {

            if (m_isDirty) return;

            m_isDirty = true;
            for (Entity e : m_children) {
                m_registry->get<Transform>(e).m_isDirty = true;
            }
        }

        inline void updateTotalTransform() {

            m_isDirty = m_local.isDirty();

            throw "not implemented";
        }
    };
}

#endif //SAXION_Y2Q1_CPP_TRANSFORM_H
