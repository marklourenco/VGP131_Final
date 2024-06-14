#ifndef WEAPONCOMPONENT_H
#define WEAPONCOMPONENT_H

#include "Component.h"

#include <iostream>
#include <vector>

using namespace std;

class WeaponComponent : public Component
{
private:
    int weaponDamage;
public:
    WeaponComponent(int weaponDamage) : weaponDamage(weaponDamage), Component() {}
    int getHealth() {
        return weaponDamage;
    }
    void setWeaponDamage(int newWeaponDamage) {
        weaponDamage = newWeaponDamage;
    }
    void PrintComponent() override {
        cout << "Weapon Damage: " << weaponDamage << endl;
    }
};

#endif