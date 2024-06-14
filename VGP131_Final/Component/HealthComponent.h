#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Component.h"

#include <iostream>
#include <vector>

using namespace std;

class HealthComponent : public Component
{
private:
    int health;
public:

    HealthComponent(int health) : health(health), Component() {}
    int getHealth()
    {
        return health;
    }

    void setHealth(int newHealth)
    {
        health = newHealth;
    }

    void PrintComponent() override
    {
        cout << "Health: " << health << endl;
    }
};

#endif