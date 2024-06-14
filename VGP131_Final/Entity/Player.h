#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"


#include <iostream>


class Player : public Entity
{
public:
	Player(const string& name, int health, int weapon) : Entity(name) {
		addComponent(make_shared<HealthComponent>(health));
		addComponent(make_shared<WeaponComponent>(weapon));
	}
};

#endif
