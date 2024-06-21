#ifndef DAMAGECOMPONENT_H
#define DAMAGECOMPONENT_H

#include "Component.h"

#include <iostream>
#include <vector>

using namespace std;

class DamageComponent : public Component
{
private:
    int damage;
public:
    DamageComponent(int damage) : damage(damage), Component() {}
    int getDamage() {
        return damage;
    }
    void setDamage(int newDamage) {
        damage = newDamage;
    }
    void PrintComponent() override {
        cout << "Damage: " << damage << endl;
    }
};

#endif