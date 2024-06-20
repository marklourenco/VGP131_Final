#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <map>
#include <memory>

#include "Entities.h"
#include "Components.h"
#include "Systems.h"

using namespace std;

class ECSEngine {
private:


    int nextEntityId;
    int nextSystemId = 100;
    map<int, unique_ptr<Entity>> entities;
    map<int, unique_ptr<System>> systems;

    // 1    Player
    // 2    Drake

    // 100  DamageSystem

public:
    ECSEngine() : nextEntityId(1) {}

    // Create entities

    Player& createPlayer(const string& name, int initialHp, int initialDamage) {
        entities[nextEntityId] = make_unique<Player>(nextEntityId, name, initialHp, initialDamage);
        return static_cast<Player&>(*entities[nextEntityId++]);
    }

    Enemy& createEnemy(const string& name, int initialHp, int initialDamage) {
        entities[nextEntityId] = make_unique<Enemy>(nextEntityId, name, initialHp, initialDamage);
        return static_cast<Enemy&>(*entities[nextEntityId++]);
    }

    // NARDA 3 ------------------

    Longsword& createLongsword(const string & name, int initialDamage) {
		entities[nextEntityId] = make_unique<Longsword>(nextEntityId, name, initialDamage);
		return static_cast<Longsword&>(*entities[nextEntityId++]);
	}
    
    HealSkill& createHealSkill(const string& name, int initialHeal) {
        entities [nextEntityId] = make_unique<HealSkill>(nextEntityId, name, initialHeal);
        return static_cast<HealSkill&>(*entities[nextEntityId++]);
    }
    
    BashSkill& createBashSkill(const string& name, int initialBash) {
		entities[nextEntityId] = make_unique<BashSkill>(nextEntityId, name, initialBash);
		return static_cast<BashSkill&>(*entities[nextEntityId++]);
	}

    Quest& createQuest(const string& name, int initialQuest, int initialQuestComplete) {
        entities[nextEntityId] = make_unique<Quest>(nextEntityId, name, initialQuest, initialQuestComplete);
        return static_cast<Quest&>(*entities[nextEntityId++]);
    }
    // ------------------

    // Create Systems

    HealthSystem& createHealthSystem() {
        systems[nextSystemId] = make_unique<HealthSystem>(nextSystemId);
        return static_cast<HealthSystem&>(*systems[nextSystemId++]);
    }

    // MORGAN 2 ------------------

    QuestSystem& createQuestSystem() {
        systems[nextSystemId] = make_unique<QuestSystem>(nextSystemId);
        return static_cast<QuestSystem&>(*systems[nextSystemId++]);
    }

    CombatSystem& createCombatSystem() {
        systems[nextSystemId] = make_unique<CombatSystem>(nextSystemId);
        return static_cast<CombatSystem&>(*systems[nextSystemId++]);
    }
    RenderSystem& createRenderSystem() {
        systems[nextSystemId] = make_unique<RenderSystem>(nextSystemId);
        return static_cast<RenderSystem&>(*systems[nextSystemId++]);
    }
    InputSystem& createInputSystem() {
        systems[nextSystemId] = make_unique<InputSystem>(nextSystemId);
        return static_cast<InputSystem&>(*systems[nextSystemId++]);
    }
    // ------------------

    // Get entities
    Entity* getEntity(int entityId) {
        auto it = entities.find(entityId);
        if (it != entities.end()) {
            return it->second.get();
        }
        return nullptr;
    }

    System* getSystem(int entityId) {
        auto it = systems.find(entityId);
        if (it != systems.end()) {
            return it->second.get();
        }
        return nullptr;
    }


    // Get components

    HealthComponent* getEnemyHealthComponent(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            if (auto enemy = dynamic_cast<Enemy*>(entity)) {
                return &enemy->getHealthComponent();
            }
        }
        return nullptr;
    }

    HealthComponent* getPlayerHealthComponent(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            if (auto player = dynamic_cast<Player*>(entity)) {
                return &player->getHealthComponent();
            }
        }
        return nullptr;
    }

    DamageComponent* getEnemyDamageComponent(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            if (auto enemy = dynamic_cast<Enemy*>(entity)) {
                return &enemy->getDamageComponent();
            }
        }
        return nullptr;
    }


    // NARDA 4 ------------------
    
    HealSkillComponent* getHealSkillComponent(int entityId) {
		Entity* entity = getEntity(entityId);
        if (entity) {
            if (auto healSkill = dynamic_cast<HealSkill*>(entity)) {
				return &healSkill->getHealComponent();
			}
		}
		return nullptr;
	}

    BashSkillComponent* getBashSkillComponent(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            if (auto bashSkill = dynamic_cast<BashSkill*>(entity)) {
				return &bashSkill->getBashComponent();
			}
		}
        return nullptr;
    }

    QuestComponent* getQuestComponent(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            if (auto quest = dynamic_cast<Quest*>(entity)) {
                return &quest->getQuestComponent();
            }
        }
        return nullptr;
    }

    QuestCompleteComponent* getQuestCompleteComponent(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            if (auto quest = dynamic_cast<Quest*>(entity)) {
                return &quest->getQuestCompleteComponent();
            }
        }
        return nullptr;
    }
     //------------------

    // Update game cycle (placeholder method)
    void update() {
        cout << "Updating game cycle..." << endl;
    }

    // Print individual entities and their components
    // template<typename T>
    void printEnemy(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            cout << "Entity ID: " << entity->getId() << ", Name: " << entity->getName() << endl;
            if (auto enemy = dynamic_cast<Enemy*>(entity)) {
                HealthComponent* health = &enemy->getHealthComponent();
                DamageComponent* damage = &enemy->getDamageComponent();
                cout << " - Health: " << health->hp << endl;
                cout << " - Damage: " << damage->damage << endl;
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printPlayer(int entityId) {
        Entity* entity = getEntity(entityId);
        if (entity) {
            cout << "Entity ID: " << entity->getId() << ", Name: " << entity->getName() << endl;
            if (auto player = dynamic_cast<Player*>(entity)) {
                HealthComponent* health = &player->getHealthComponent();
                cout << " - Health: " << health->hp << endl;
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    // Apply Systems
    // MORGAN 3 ------------------
    //Health System
    void damage(int entityId, string hurtName, HealthComponent* health, string damageName, int damage) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<HealthSystem*>(entity)) {
                system->damage(hurtName, *health, damageName, damage);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void heal(int entityId, string healName, HealthComponent* health, int heal, int initialHealth) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<HealthSystem*>(entity)) {
                system->heal(healName, *health, heal, initialHealth);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void bashDamage(int entityId, string hurtName, HealthComponent* health, string damageName, int damage, int bashDamage) {
            System* entity = getSystem(entityId);
            if (entity) {
                //cout << "Entity ID: " << entity->getId() << endl;
                if (auto system = dynamic_cast<HealthSystem*>(entity)) {
                    system->bashDamage(hurtName, *health, damageName, damage, bashDamage);
                }
            }
            else {
                cout << "Entity with ID " << entityId << " not found." << endl;
            }
        }

    //Render System
    void printStartMenu(int entityId, char keyStart, char keyQuit) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<RenderSystem*>(entity)) {
                system->printStartMenu(keyStart, keyQuit);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
            

    }


    void printMenu(int entityId, char keyInventory, char keyDungeon, char keyQuit, char keyStart) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<RenderSystem*>(entity)) {
                system->printMenu(keyInventory, keyDungeon, keyQuit, keyStart);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }


    void printInventoryEmpty(int entityId) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<RenderSystem*>(entity)) {
                system->printInventoryEmpty();
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printEquippedWeapon(int entityId, string weapon, int damage) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<RenderSystem*>(entity)) {
                system->printEquippedWeapon(weapon, damage);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printQuitMenu(int entityId) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<RenderSystem*>(entity)) {
                system->printQuitMenu();
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    
    //Combat System

    void printDungeonMenu(int entityId) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<CombatSystem*>(entity)) {
                system->printDungeonMenu();
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }
    void printCombatStatus(int entityId, string monster, HealthComponent* health, HealthComponent* enemyHealth) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<CombatSystem*>(entity)) {
                system->printCombatStatus(monster, *health, *enemyHealth);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printCombatActions(int entityId) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<CombatSystem*>(entity)) {
                system->printCombatActions();
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printSkill(int entityId) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<CombatSystem*>(entity)) {
                system->printSkill();
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printDungeonTransition(int entityId) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<CombatSystem*>(entity)) {
                system->printDungeonTransition();
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void escape(int entityId, HealthComponent* health, HealthComponent* enemyHealth, int initialHealth, int enemyInitialHealth) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<CombatSystem*>(entity)) {
                system->escape(*health, *enemyHealth, initialHealth, enemyInitialHealth);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }
    void recover(int entityId, HealthComponent* health, HealthComponent* enemyHealth, int initialHealth, int enemyInitialHealth) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<CombatSystem*>(entity)) {
                system->recover(*health, *enemyHealth, initialHealth, enemyInitialHealth);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }
    //Quest System
    void setProgress(int entityId, QuestComponent* quest) {
        System* entity = getSystem(entityId);
        if (entity) {
            if (auto system = dynamic_cast<QuestSystem*>(entity)) {
                system->setProgress(*quest);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void setQuestComplete(int entityId, QuestCompleteComponent* questComplete) {
        System* entity = getSystem(entityId);
        if (entity) {
            if (auto system = dynamic_cast<QuestSystem*>(entity)) {
                system->setQuestComplete(*questComplete);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printQuest(int entityId, QuestCompleteComponent* questComplete, string enemy) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<QuestSystem*>(entity)) {
                system->printQuest(*questComplete, enemy);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printQuestProgress(int entityId,
        QuestCompleteComponent* questComplete1, string enemy1, QuestComponent* quest1,
        QuestCompleteComponent* questComplete2, string enemy2, QuestComponent* quest2,
        QuestCompleteComponent* questComplete3, string enemy3, QuestComponent* quest3) {
        System* entity = getSystem(entityId);
        if (entity) {
            if (auto system = dynamic_cast<QuestSystem*>(entity)) {
                system->printQuestProgress(*questComplete1, enemy1, *quest1,
                    *questComplete2, enemy2, *quest2,
                    *questComplete3, enemy3, *quest3);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void printRecieveQuest(int entityId, char keyQuest) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<QuestSystem*>(entity)) {
                system->printRecieveQuest(keyQuest);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }


    }

    void printRecieveQuestReward(int entityId, char keyQuest) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<QuestSystem*>(entity)) {
                system->printRecieveQuestReward(keyQuest);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void completeQuest(int entityId, int haveQuest, int countQuest) {
        System* entity = getSystem(entityId);
        if (entity) {
            if (auto system = dynamic_cast<QuestSystem*>(entity)) {
                system->completeQuest(haveQuest, countQuest);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    //Input System
    char input(int entityId, char input) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<InputSystem*>(entity)) {
                return system->input(input);
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    void invalidInput(int entityId) {
        System* entity = getSystem(entityId);
        if (entity) {
            //cout << "Entity ID: " << entity->getId() << endl;
            if (auto system = dynamic_cast<InputSystem*>(entity)) {
                system->invalidInput();
            }
        }
        else {
            cout << "Entity with ID " << entityId << " not found." << endl;
        }
    }

    // ------------------

};

#endif