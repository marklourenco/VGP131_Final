#ifndef DRAGON_H
#define DRAGON_H

#include "Entity.h"
#include "HealthComponent.h"
#include "DamageComponent.h"

#include <iostream>


class Dragon : public Entity
{
public:
	Dragon(const string& name, int health, int damage) : Entity(name) 
	{
		addComponent(make_shared<HealthComponent>(health)); 
		addComponent(make_shared<DamageComponent>(damage)); 
	}
};

#endif

