//
// Created by Maksym Maisak on 22/10/18.
//

#ifndef SAXION_Y2Q1_CPP_COMPONENTPOOL_H
#define SAXION_Y2Q1_CPP_COMPONENTPOOL_H

#include "Entity.h"
#include <map>

class ComponentPoolBase {};

template<typename TComponent>
class ComponentPool : public ComponentPoolBase, public std::map<Entity, TComponent> {};

#endif //SAXION_Y2Q1_CPP_COMPONENTPOOL_H
