//
// Created by Maksym Maisak on 4/10/18.
//

#ifndef SAXION_Y2Q1_CPP_ENTITY_H
#define SAXION_Y2Q1_CPP_ENTITY_H

#include <vector>

class Entity {

    public:
        ~Entity();
        void destroy();

    private:
        bool _isDestroyed;
        std::vector<Entity*> _children;
};


#endif //SAXION_Y2Q1_CPP_ENTITY_H
