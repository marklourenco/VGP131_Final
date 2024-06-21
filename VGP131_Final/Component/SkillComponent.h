#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

#include "Component.h"

#include <iostream>
#include <vector>

using namespace std;

class SkillComponent : public Component
{
private:
    int skillDamage;
public:
    SkillComponent(int skillDamage) : skillDamage(skillDamage), Component() {}
    int getSkill() {
        return skillDamage;
    }
    void setSkillDamage(int newSkillDamage) {
        skillDamage = newSkillDamage;
    }
    void PrintComponent() override {
        cout << "Skill Damage: " << skillDamage << endl;
    }
};

#endif