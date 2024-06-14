#ifndef SKILL1_H
#define SKILL1_H

#include "Entity.h"
#include "SkillComponent.h"

#include <iostream>


class SkillOne : public Entity
{
public:
	SkillOne(const string& name, int skill) : Entity(name) {
		addComponent(make_shared<SkillComponent>(skill));
	}
};

#endif
