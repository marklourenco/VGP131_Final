#ifndef ECS_H
#define ECS_H


#include "Entity.h"
#include "System.h"

#include <iostream>
#include <vector>
#include <set>

class ECS {
    static vector<shared_ptr<Entity>> entities;
    static set<shared_ptr<System>> systems;
public:
    template <typename T>
    static void addEntity(shared_ptr<T> entity) {
        cout << "Adding entity '" << entity->getName() << "'" << std::endl;
        entities.emplace_back(entity);
    }
    template <typename T>
    static void addSystem(shared_ptr<T> system) {
        cout << "Adding system '" << typeid(T).name() << "'" << std::endl;
        systems.insert(system);
    }
    static void printEntities() {
        cout << "--------------------" << std::endl;
        for (auto& entity : entities)
            entity->PrintEntity();
        cout << "--------------------" << std::endl;
    }
    static void update() {
        cout << "Updating entities..." << std::endl;
        for (auto& system : systems)
            for (auto& entity : entities)
                system->Update(*entity);
    }
};
vector<shared_ptr<Entity>> ECS::entities;
set<shared_ptr<System>> ECS::systems;

#endif

