#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>
#include <unordered_map>

#include "Components.h"

using namespace std;

class Entity {
private:
    int id;
    string name;

public:
    Entity(int entityId, const string& entityName) : id(entityId), name(entityName) {}
    virtual ~Entity() {}  // Virtual destructor

    int getId() const { return id; }
    const string getName() const { return name; }

};

class Player : public Entity {
private:
    // current health
    HealthComponent health;
    // current damage
    DamageComponent damage;
    // initial hp
    int initialHp;
    // initial damage
    int initialDamage;
public:
    Player(int entityId, const string& entityName, int initialHp, int initialDamage)
        : Entity(entityId, entityName), health(initialHp), damage(initialDamage), initialHp(initialHp), initialDamage(initialDamage) {}

    HealthComponent& getHealthComponent() { return health; }
    DamageComponent& getDamageComponent() { return damage; }

    int getHealth() {
        return initialHp;
    }

    int getDamage() {
        return initialDamage;
    }
};

class Enemy : public Entity {
private:
    HealthComponent health;
    DamageComponent damage;
    int initialHp;
    int initialDamage;
public:
    Enemy(int entityId, const string& entityName, int initialHp, int initialDamage)
        : Entity(entityId, entityName), health(initialHp), damage(initialDamage), initialHp(initialHp), initialDamage(initialDamage) {}

    HealthComponent& getHealthComponent() { return health; }
    DamageComponent& getDamageComponent() { return damage; }

    int getHealth() {
        return initialHp;
    }

    int getDamage() {
        return initialDamage;
    }
};

// NARDA 1 ------------------ Creation of Entities

class Longsword : public Entity {
private:
    	DamageComponent damage;
        //Initial damage
        int initialDamage;
public:
    	Longsword(int entityId, const string& entityName, int initialDamage)
		: Entity(entityId, entityName), damage(initialDamage), initialDamage(initialDamage) {}

	//Get the damage component
        DamageComponent& getDamageComponent() { return damage; }
    
    //Get the initial damage
    int getDamage() {
		return initialDamage;
	}
};

class HealSkill : public Entity {
private: 
    HealSkillComponent heal;
	//Initial heal
    int initialHeal;
public:
    //Constructor
	HealSkill(int entityId, const string& entityName, int initialHeal)
		: Entity(entityId, entityName), heal(initialHeal), initialHeal(initialHeal) {}

    //Get the heal component
    HealSkillComponent& getHealComponent() { return heal; }

     //Get the initial heal
    int getHeal() {
        return initialHeal;
    }
};

class BashSkill : public Entity {
private: 
    BashSkillComponent bash;
	int initialBash;
public:
    BashSkill(int entityId, const string& entityName, int initialBash)
		: Entity(entityId, entityName), bash(initialBash), initialBash(initialBash) {}

	BashSkillComponent& getBashComponent() { return bash; }
    
    //Get the initial bash
    int getBash() {
        return initialBash;
	}
};

class Quest : public Entity {

   // Get the initial quest
private:
    QuestComponent quest;
    QuestCompleteComponent questComplete;
    int initialQuest;
    int initialQuestComplete;
public:
    Quest(int entityId, const string& entityName,int initialQuest, int initialQuestComplete)
        : Entity(entityId, entityName), quest(initialQuest), questComplete(initialQuestComplete), initialQuest(initialQuest), initialQuestComplete(initialQuestComplete) {}

    QuestComponent& getQuestComponent() { return quest; }
    QuestCompleteComponent& getQuestCompleteComponent() { return questComplete; }

    int getQuest() {
        return initialQuest;
    }

    int getQuestComplete() {
        return initialQuestComplete;
    }
};

// ------------------

#endif