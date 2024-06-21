#ifndef QUEST_H
#define QUEST_H

#include "Entity.h"
#include "QuestComponent.h"

#include <iostream>


class Quest : public Entity
{
public:
	Quest(const string& name, int quest) : Entity(name) {
		addComponent(make_shared<QuestComponent>(quest));
	}
};

#endif


