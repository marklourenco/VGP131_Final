#ifndef DRAKE_H
#define DRAKE_H

#include "Entity.h"
#include "HealthComponent.h"
#include "DamageComponent.h"
#include <iostream>


class Drake : public Entity
{
public:
	Drake(const string& name, int health, int damage) : Entity(name) 
	{
	
		addComponent(make_shared<HealthComponent>(health)); 
		addComponent(make_shared<DamageComponent>(damage)); 

	}
};

#endif
