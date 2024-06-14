#ifndef LONGSWORD_H
#define LONGSWORD_H

#include "Entity.h"
#include "DamageComponent.h"

#include <iostream>


class Longsword : public Entity
{
public:
	Longsword(const string& name, int damage) : Entity(name) 
	{
		addComponent(make_shared<DamageComponent>(damage)); 

	}
};

#endif
