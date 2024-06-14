#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "System.h"
#include "HealthComponent.h"

using namespace std;

class DamageSystem : public System
{
public:
    void Update(Entity& entity) override {
        int damage = 10;

        auto health = entity.GetComponent<HealthComponent>();

        if (health == nullptr)
            return;

        cout << "Damaging entity '" << entity.getName() << "' with " << damage << " damage" << std::endl;

        health->setHealth(health->getHealth() - damage);
    }
};

#endif