#include <iostream>

#include "Player.h"

#include "DamageSystem.h"

#include "ECS.h"

int main()
{
    // Entities

    ECS::addEntity(make_shared<Player>("Player Morgan", 100));
    
    // Systems

    ECS::addSystem(make_shared<DamageSystem>());

    // Print Entities

    ECS::printEntities();

    // Update Systems

    ECS::update();

    // Print Entities

    ECS::printEntities();

    return 0;
}