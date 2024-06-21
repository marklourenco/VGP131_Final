#ifndef WYRMLING_H
#define WYRMLING_H

#include "Entity.h"
#include "HealthComponent.h"
#include "DamageComponent.h"

#include <iostream>


class Wyrmling : public Entity
{
public:
	Wyrmling(const string& name, int health, int damage) : Entity(name) 
	{
		addComponent(make_shared<HealthComponent>(health));
		addComponent(make_shared<DamageComponent>(damage)); 
	}
};

#endif
