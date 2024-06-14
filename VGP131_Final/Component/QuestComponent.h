#ifndef QUESTCOMPONENT_H
#define QUESTCOMPONENT_H

#include "Component.h"

#include <iostream>
#include <vector>

using namespace std;

class QuestComponent : public Component
{
private:
    int questGoal = 3;
    int quest = 0;
public:

    QuestComponent(int quest) : quest(quest), Component() {}
    int getQuest()
    {
        return quest;
    }

    void setQuest(int newQuest)
    {
        quest = newQuest;
    }

    QuestComponent() : quest(), questGoal(), Component() {}
    int getQuestOne() {
        return quest;
    }
    /*void increaseQuest() {
        quest++;
    }*/
    void printQuestOne() {
        cout << "Quest Progress: " << quest << " out of " << questGoal << endl;
    }
};

#endif