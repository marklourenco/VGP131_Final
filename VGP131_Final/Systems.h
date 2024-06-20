#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <iostream>
#include <string>

#include "Components.h"

using namespace std;

class System {
private:
    int id;
    unordered_map<int, Entity*> entities;

public:
    System(int systemId) : id(systemId) {}
    virtual ~System() {}  // Virtual destructor

    int getId() const { return id; }

    void addEntity(Entity* entity) {
        entities[entity->getId()] = entity;
    }

    Entity* getEntity(int entityId) {
        auto it = entities.find(entityId);
        if (it != entities.end()) {
            return it->second;
        }
        return nullptr;
    }

    string getEntityName(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            return entity->getName();
        }
        cout << "Entity with ID " << entityId << " not found." << endl;
    }

};
// MORGAN 1 ------------------
class HealthSystem : public System {
public:
    HealthSystem(int entityId) : System(entityId) {}
    void damage(string hurtName, HealthComponent& health, string damageName, int damage) {
        health.hp -= damage;
        cout << damageName << " inflicted " << damage << " damage to " << hurtName << ".\n"
            << hurtName << " current HP: " << health.hp << endl;
    }

    void heal(string healName, HealthComponent& health, int heal, int initialHealth) {
        if (health.hp += heal >= initialHealth)
            health.hp = initialHealth;
        else
            health.hp += heal;
        cout << healName << " healed " << heal << " life points.\n"
            << healName << " current HP: " << health.hp << endl;
    }

    void bashDamage(string hurtName, HealthComponent& health, string damageName, int damage, int bashDamage) {
        health.hp -= damage + bashDamage;
        cout << damageName << " inflicted " << damage + bashDamage << " damage to " << hurtName << ".\n"
            << hurtName << " current HP: " << health.hp << endl;
    }

};

class QuestSystem : public System {
private:
public:
    QuestSystem(int entityId) : System(entityId) {}

    void setProgress(QuestComponent& quest) {
        quest.quest++;
    }
    void setQuestComplete(QuestCompleteComponent& questComplete) {
        questComplete.questComplete--;
    }

    void printQuest(QuestCompleteComponent& questComplete, string enemy)
    {
        cout << "You have received a quest!" << endl;
        cout << "Kill " << questComplete.questComplete << " " << enemy << "\t\t" << "0/" << questComplete.questComplete << endl;
    }

    void printQuestProgress(QuestCompleteComponent& questComplete1, string enemy1, QuestComponent& quest1
        , QuestCompleteComponent& questComplete2, string enemy2, QuestComponent& quest2, 
        QuestCompleteComponent& questComplete3, string enemy3, QuestComponent& quest3)
    {
        cout << "Quest Progress:" << endl;
        cout << "Kill " << questComplete1.questComplete << " " << enemy1 << "\t\t" << quest1.quest 
            << "/" << questComplete1.questComplete << endl;
        cout << "Kill " << questComplete2.questComplete << " " << enemy2 << "\t\t" << quest2.quest
            << "/" << questComplete2.questComplete << endl;
        cout << "Kill " << questComplete3.questComplete << " " << enemy3 << "\t\t" << quest3.quest
            << "/" << questComplete3.questComplete << endl;
        cout << "----------------------------" << endl;
    }

    void printRecieveQuest(char keyQuest)
    {
        cout << "Press " << keyQuest << " to Receive a Quest" << endl;
    }

    void printRecieveQuestReward(char keyQuest)
    {
        cout << "Press " << keyQuest << " to Collect the Quest Reward" << endl;
    }

    void completeQuest(int haveQuest, int countQuest) {
        cout << "You have completed all the Quest!" << endl;
        cout << "----------------------------" << endl;
        haveQuest = 0;
        countQuest = 0;
    }
};

class CombatSystem : public System {
private:
public:
    CombatSystem(int entityId) : System(entityId) {}

    void escape(HealthComponent& health, HealthComponent& enemyHealth, int initialHealth, int enemyInitialHealth)
    {
        cout << "You have escaped from combat!" << endl;
        cout << "You regained all your health" << endl;
        health.hp = initialHealth;
        enemyHealth.hp = enemyInitialHealth;

    }
    void recover(HealthComponent& health, HealthComponent& enemyHealth, int initialHealth, int enemyInitialHealth)
    {
        cout << "You Won!!" << endl;
        cout << "You regained all your health" << endl;
        health.hp = initialHealth;

    }

    void printCombatStatus(string monster, HealthComponent& health, HealthComponent& enemyHealth)
    {
        cout << "In Combat With: " << monster << endl;
        cout << monster << " health: " << enemyHealth.hp << endl;
        cout << "Player" << " health: " << health.hp << endl;
        cout << "----------------------------" << endl;

    }

    void printCombatActions()
    {
        cout << "Actions:" << endl;
        cout << "\t A. Basic Attack" << endl;
        cout << "\t B. Skill" << endl;
        cout << "\t V. Escape" << endl;
    }

    void printSkill()
    {
        cout << "Skills:" << endl;
        cout << "\t A. Bash the enemy!" << endl;
        cout << "\t B. Heal myself" << endl;
    }

    void printDungeonMenu()
    {
        cout << "Which Monster would you like to fight?" << endl;
        cout << "\t A. Wyrmling" << endl;
        cout << "\t B. Dragon" << endl;
        cout << "\t C. Drake" << endl;
        cout << "Press " << "F" << " to Main Menu" << endl;

    }

    void printDungeonTransition()
    {
        cout << "Telepoting to the dungeon lobby..." << endl;

    }
};

class RenderSystem : public System {
private:
public:
    RenderSystem(int entityId) : System(entityId) {}


    void printStartMenu(char keyStart, char keyQuit)
    {
        cout << "A Basic RPG GAME" << endl;
        cout << "----------------------------" << endl;
        cout << "Press " << keyStart << " to Start" << endl;
        cout << "Press " << keyQuit << " to Quit" << endl;
    }

    void printMenu(char keyInventory, char keyDungeon, char keyQuit, char keyStart)
    {
        cout << "Press " << keyStart << " to Main Menu" << endl;
        cout << "Press " << keyInventory << " to Equip Weapon" << endl;
        cout << "Press " << keyDungeon << " to Enter the Dungeon" << endl;
        cout << "Press " << keyQuit << " to Quit" << endl;
    }

    void printInventoryEmpty() {
        cout << "Your Inventory is empty." << endl;
        cout << "---------------------------------------" << endl;
    }

    void printEquippedWeapon(string weapon, int damage) {
        cout << "You have equipped " << weapon << " (Damage +" << damage << ")" << endl;
        cout << "---------------------------------------" << endl;
    }

    void printQuitMenu()
    {
        cout << "Quit Game?" << endl;
        cout << "Press X to Quit" << endl;
        cout << "Press R to return to Game" << endl;
    }
        
};

class InputSystem : public System {
private:
public:
    InputSystem(int entityId) : System(entityId) {}

    char input(char input)
    {
        cout << "\nEnter your choice: ";
        cin >> input;
        return input;
    }

    void invalidInput() {
        cout << "Invalid Input! Try Again! " << endl;
    }
};


// ---------------------------

#endif