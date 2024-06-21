#ifndef SKILL2_H
#define SKILL2_H

#include "Entity.h"
#include "SkillComponent.h"

#include <iostream>


class SkillTwo : public Entity
{
public:
	SkillTwo(const string& name, int skill) : Entity(name) {
		addComponent(make_shared<SkillComponent>(skill));
	}
};

#endif

