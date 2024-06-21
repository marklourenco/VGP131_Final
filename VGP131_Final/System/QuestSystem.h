#ifndef QUESTSYSTEM_H
#define QUESTSYSTEM_H
#include "System.h"
#include "QuestComponent.h"
#include "Component.h"


using namespace std;

class QuestSystem : public System
{
    void increaseQuest(Entity& entity)
    {
        auto quest = entity.GetComponent<QuestComponent>();
        entity.setQuest<QuestComponent>(quest + 1);

    }
};
#endif