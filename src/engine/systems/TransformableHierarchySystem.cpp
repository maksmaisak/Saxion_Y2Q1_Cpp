//
// Created by Maksym Maisak on 4/11/18.
//

#include "TransformableHierarchySystem.h"

namespace en {

    void TransformableHierarchySystem::receive(const ComponentWillBeRemoved<Transformable>& info) {

        for (Entity child : info.component.m_children) {
            m_registry->destroy(child);
        }
    }
}
