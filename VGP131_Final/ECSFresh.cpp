#include <iostream> 
#include <string>
#include "Engine.h"

using namespace std;


int main() {
    ECSEngine ecs;

    // Create entities
    auto& player = ecs.createPlayer("Player 1", 100, 20);
    auto& zero = ecs.createPlayer("Zero", 0, 0);
    auto& enemy1 = ecs.createEnemy("Wyrmling", 50, 10);
    auto& enemy2 = ecs.createEnemy("Dragon", 40, 10);
    auto& enemy3 = ecs.createEnemy("Drake", 40, 10);
    auto& quest1 = ecs.createQuest("Quest 1: Wyrmling", 0, 1);
    auto& quest2 = ecs.createQuest("Quest 2: Dragon", 0, 1);
    auto& quest3 = ecs.createQuest("Quest 3: Drake", 0, 1);


    //Create quests
    
    // NARDA 5 ------------------
    auto& longsword = ecs.createLongsword("Longsword", 20);
    auto& healSkill = ecs.createHealSkill("HealSkill", 20);
    auto& bashSkill = ecs.createBashSkill("BashSkill", 30);

    // ------------------

    // Create systems

    auto& healthSystem = ecs.createHealthSystem();

    // MORGAN 4 ------------------

    auto& questSystem = ecs.createQuestSystem();
    auto& combatSystem = ecs.createCombatSystem();
    auto& renderSystem = ecs.createRenderSystem();
    auto& InputSystem = ecs.createInputSystem();

    //------------------
    HealthComponent* playerHealth = ecs.getPlayerHealthComponent(player.getId());
    HealthComponent* zeroHealth = ecs.getPlayerHealthComponent(player.getId());
    HealthComponent* enemy1Health = ecs.getEnemyHealthComponent(enemy1.getId());
    HealthComponent* enemy2Health = ecs.getEnemyHealthComponent(enemy2.getId());
    HealthComponent* enemy3Health = ecs.getEnemyHealthComponent(enemy3.getId());
    QuestComponent* quest1Quest = ecs.getQuestComponent(quest1.getId());
    QuestComponent* quest2Quest = ecs.getQuestComponent(quest2.getId());
    QuestComponent* quest3Quest = ecs.getQuestComponent(quest3.getId());
    QuestCompleteComponent* quest1Complete = ecs.getQuestCompleteComponent(quest1.getId());
    QuestCompleteComponent* quest2Complete = ecs.getQuestCompleteComponent(quest2.getId());
    QuestCompleteComponent* quest3Complete = ecs.getQuestCompleteComponent(quest3.getId());

    string playerName = player.getName();
    string enemy1Name = enemy1.getName();
    string enemy2Name = enemy2.getName();
    string enemy3Name = enemy3.getName();
    string weaponName = longsword.getName();
    int enemy1InitialHealth = enemy1.getHealth();
    int enemy2InitialHealth = enemy2.getHealth();
    int enemy3InitialHealth = enemy3.getHealth();
    int playerInitialHealth = player.getHealth();

   int inGame = 1;
    int haveQuest = 0;
    int countQuest = 0;
    int completeQuest = 3;
    int inventoryEmpty = 1;
    int inCombat = 0;
    char input = 'Z';
    const char menuInput = 'F';
    const char questInput = 'Q';
    const char inventoryInput = 'E';
    const char dungeonInput = 'D';
    const char quitInput = 'X';
    const char returnInput = 'R';
    const char c1Input = 'A';
    const char c2Input = 'B';
    const char c3Input = 'C';
    const char c4Input = 'V';

    //GAME START------------------------------------------------------------
 
    //Start Menu
    ecs.printStartMenu(renderSystem.getId(), menuInput, quitInput);
    input = ecs.input(InputSystem.getId(), input);
    
    //MainMenu
    if (input == menuInput)
    {
        system("cls");
        goto menu;
        while (inGame == 1)
        {
            choice:
            cout << endl;
            input = ecs.input(InputSystem.getId(), input);
            //PRESS F
            if (input == menuInput) {
            menu:
                cout << endl;
                if (haveQuest == 0) 
                {
                    //Print Quest
                    ecs.printQuest(questSystem.getId(), quest1Complete, enemy1Name);
                    ecs.printQuest(questSystem.getId(), quest2Complete, enemy2Name);
                    ecs.printQuest(questSystem.getId(), quest3Complete, enemy3Name);
                    haveQuest++;
                    //Print a New Menu
                    goto menu;
                }
                //have quest,but incomplete
                if (countQuest < completeQuest && haveQuest == 1)
                {
                    ecs.printQuestProgress(questSystem.getId(), quest1Complete, enemy1Name, quest1Quest,
                        quest2Complete, enemy2Name, quest2Quest, quest3Complete, enemy3Name, quest3Quest);
                    ecs.printMenu(renderSystem.getId(), inventoryInput, dungeonInput, quitInput, menuInput);
                    goto choice;
                }
                //Completed Quest
                if (countQuest >= completeQuest) 
                {
                    ecs.completeQuest(questSystem.getId(), haveQuest, countQuest);
                    ecs.printMenu(renderSystem.getId(), inventoryInput, dungeonInput, quitInput, menuInput);
                    goto choice;
                }
                else 
                {
                    cout << "Error" << endl;
                    goto choice;
                }
            }

            //PRESS E
            if (input == inventoryInput)
            {
                system("cls");
            inventory:
                cout << endl;
                ecs.printEquippedWeapon(renderSystem.getId(), weaponName, longsword.getDamage());
                ecs.printMenu(renderSystem.getId(), inventoryInput, dungeonInput, quitInput, menuInput);
                goto choice;
            }

            //PRESS Q
            if (input == quitInput)
            {
                system("cls");
                goto quit;
            }

            //PRESS D
            if (input == dungeonInput)
            {
                system("cls");
            dungeon:
                cout << countQuest << endl;
                if (countQuest >= completeQuest)
                {
                    cout << "Quest Completed!, redirecting to menu." << endl;
                    goto menu;
                }
                cout << endl;
                ecs.printDungeonTransition(combatSystem.getId());
                ecs.printDungeonMenu(combatSystem.getId());
                input = ecs.input(InputSystem.getId(), input);
                if (input == c1Input)
                {
                    inCombat = 1;
                    combat1:
                    while (inCombat == 1)
                    {
                        int enemy1hp = enemy1.getHealth();
                        //Combat Loop
                        system("cls");
                        cout << endl;
                        ecs.printCombatStatus(combatSystem.getId(), enemy1.getName(), playerHealth, enemy1Health);
                        ecs.printCombatActions(combatSystem.getId());
                        cout << endl;
                        input = ecs.input(InputSystem.getId(), input);
                        //Basic Attack
                        if (input == c1Input)
                        {
                            system("cls");
                            //player attack
                            ecs.damage(healthSystem.getId(), enemy1Name, enemy1Health, playerName, player.getDamage());


                            if (enemy1Health->hp <= 0)
                            {
                                ecs.setProgress(questSystem.getId(), quest1Quest);
                                ecs.recover(combatSystem.getId(), playerHealth, enemy1Health, playerInitialHealth, enemy1InitialHealth);
                                inCombat = 0;
                                goto dungeon;
                            }
                            if (playerHealth->hp <= 0)
                            {
                                cout << "You have no health! Escape!" << endl;
                                inCombat = 0;
                                goto escape;
                            }
                            else
                            {
                                ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy1Name, enemy1.getDamage());
                                goto combat1;
                            }
                        }

                        //Skills
                        if (input == c2Input)
                        {
                            system("cls");
                            ecs.printSkill(combatSystem.getId());
                            input = ecs.input(InputSystem.getId(), input);
                            //Skill 1 Bash
                            if (input == c1Input)
                            {
                                ecs.bashDamage(healthSystem.getId(), enemy1Name, enemy1Health, playerName, player.getDamage(), bashSkill.getBash());


                                if (enemy1Health->hp <= 0)
                                {
                                    ecs.setProgress(questSystem.getId(), quest1Quest);
                                    ecs.recover(combatSystem.getId(), playerHealth, enemy1Health, playerInitialHealth, enemy1InitialHealth);
                                    inCombat = 0;
                                    goto dungeon;
                                }
                                if (playerHealth->hp <= 0)
                                {
                                    cout << "You have no health! Escape!" << endl;
                                    inCombat = 0;
                                    goto escape;
                                }
                                else
                                {
                                    ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy1Name, enemy1.getDamage());
                                    goto combat1;
                                }
                            }

                            //SKill 2 Heal
                            if (input == c2Input)
                            {
                                system("cls");
                                ecs.heal(healthSystem.getId(), playerName, playerHealth, healSkill.getHeal(), playerInitialHealth);
                                ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy1Name, enemy1.getDamage());
                                goto combat1;

                            }

                            //Escape
                            if (input == c4Input)
                            {
                                goto escape;
                            }
                        }

                        //Escape Dungeon
                        if (input == c4Input)
                        {
                            escape:
                            ecs.escape(combatSystem.getId(), playerHealth, enemy1Health, playerInitialHealth, enemy1InitialHealth);
                            inCombat = 0;
                            goto dungeon;
                        }
                        //Combat loop Ends
                    }
                }

                //Dragon Combat
                if (input == c2Input)
                {
                    inCombat = 1;
                combat2:
                    while (inCombat == 1)
                    {
                        //Combat Loop
                        system("cls");
                        cout << endl;
                        ecs.printCombatStatus(combatSystem.getId(), enemy2.getName(), playerHealth, enemy2Health);
                        ecs.printCombatActions(combatSystem.getId());
                        cout << endl;
                        input = ecs.input(InputSystem.getId(), input);
                        //Basic Attack
                        if (input == c1Input)
                        {
                            system("cls");
                            //player attack
                            ecs.damage(healthSystem.getId(), enemy2Name, enemy2Health, playerName, player.getDamage());

                            if (enemy2Health->hp <= 0)
                            {
                                ecs.setProgress(questSystem.getId(), quest2Quest);
                                ecs.recover(combatSystem.getId(), playerHealth, enemy2Health, playerInitialHealth, enemy2InitialHealth);
                                inCombat = 0;
                                goto dungeon;
                            }
                            if (playerHealth->hp <= 0)
                            {
                                cout << "You have no health! Escape!" << endl;
                                inCombat = 0;
                                goto escape2;
                            }
                            else
                            {
                                ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy2Name, enemy2.getDamage());
                                goto combat2;
                            }
                        }

                        //Skills
                        if (input == c2Input)
                        {
                            system("cls");
                            ecs.printSkill(combatSystem.getId());
                            input = ecs.input(InputSystem.getId(), input);
                            //Skill 1 Bash
                            if (input == c1Input)
                            {
                                ecs.bashDamage(healthSystem.getId(), enemy2Name, enemy2Health, playerName, player.getDamage(), bashSkill.getBash());

                                if (enemy2Health->hp <= 0)
                                {
                                    ecs.setProgress(questSystem.getId(), quest2Quest);
                                    ecs.recover(combatSystem.getId(), playerHealth, enemy2Health, playerInitialHealth, enemy2InitialHealth);
                                    inCombat = 0;
                                    goto dungeon;
                                }
                                if (playerHealth->hp <= 0)
                                {
                                    cout << "You have no health! Escape!" << endl;
                                    inCombat = 0;
                                    goto escape2;
                                }
                                else
                                {
                                    ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy2Name, enemy2.getDamage());
                                    goto combat2;
                                }
                            }

                            //SKill 2 Heal
                            if (input == c2Input)
                            {
                                system("cls");
                                ecs.heal(healthSystem.getId(), playerName, playerHealth, healSkill.getHeal(), playerInitialHealth);
                                ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy2Name, enemy2.getDamage());
                                goto combat2;

                            }

                            //Escape
                            if (input == c4Input)
                            {
                                goto escape2;
                            }
                        }

                        //Escape Dungeon
                        if (input == c4Input)
                        {
                        escape2:
                            ecs.escape(combatSystem.getId(), playerHealth, enemy2Health, playerInitialHealth, enemy2InitialHealth);
                            inCombat = 0;
                            goto dungeon;
                        }
                        //Combat loop Ends
                    }
                }

                //Drake Combat
                if (input == c3Input)
                {
                    inCombat = 1;
                combat3:
                    while (inCombat == 1)
                    {
                        //Combat Loop
                        system("cls");
                        cout << endl;
                        ecs.printCombatStatus(combatSystem.getId(), enemy3.getName(), playerHealth, enemy3Health);
                        ecs.printCombatActions(combatSystem.getId());
                        cout << endl;
                        input = ecs.input(InputSystem.getId(), input);
                        //Basic Attack
                        if (input == c1Input)
                        {
                            system("cls");
                            //player attack
                            ecs.damage(healthSystem.getId(), enemy3Name, enemy3Health, playerName, player.getDamage());

                            if (enemy3Health->hp <= 0)
                            {
                                ecs.setProgress(questSystem.getId(), quest3Quest);
                                ecs.recover(combatSystem.getId(), playerHealth, enemy3Health, playerInitialHealth, enemy3InitialHealth);
                                inCombat = 0;
                                goto dungeon;
                                break;
                            }
                            if (playerHealth->hp <= 0)
                            {
                                ecs.printCombatStatus(combatSystem.getId(), enemy3.getName(), playerHealth, enemy3Health);
                                cout << "You have no health! Escape!" << endl;
                                inCombat = 0;
                                goto escape3;
                            }
                            else
                            {
                                ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy3Name, enemy3.getDamage());
                                goto combat3;
                            }
                        }

                        //Skills
                        if (input == c2Input)
                        {
                            system("cls");
                            ecs.printSkill(combatSystem.getId());
                            input = ecs.input(InputSystem.getId(), input);
                            //Skill 1 Bash
                            if (input == c1Input)
                            {
                                ecs.bashDamage(healthSystem.getId(), enemy3Name, enemy3Health, playerName, player.getDamage(), bashSkill.getBash());

                                if (enemy3Health->hp <= 0)
                                {
                                    ecs.setProgress(questSystem.getId(), quest3Quest);
                                    ecs.recover(combatSystem.getId(), playerHealth, enemy3Health, playerInitialHealth, enemy3InitialHealth);
                                    inCombat = 0;
                                    goto dungeon;
                                }
                                if (playerHealth->hp <= 0)
                                {
                                    cout << "You have no health! Escape!" << endl;
                                    inCombat = 0;
                                    goto escape3;
                                }
                                else
                                {
                                    ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy3Name, enemy3.getDamage());
                                    goto combat3;
                                }
                            }

                            //SKill 2 Heal
                            if (input == c2Input)
                            {
                                system("cls");
                                ecs.heal(healthSystem.getId(), playerName, playerHealth, healSkill.getHeal(), playerInitialHealth);
                                ecs.damage(healthSystem.getId(), playerName, playerHealth, enemy3Name, enemy3.getDamage());
                                goto combat3;
                            }

                            //Escape
                            if (input == c4Input)
                            {
                                goto escape3;
                            }
                        }

                        //Escape Dungeon
                        if (input == c4Input)
                        {
                        escape3:
                            ecs.escape(combatSystem.getId(), playerHealth, enemy3Health, playerInitialHealth, enemy3InitialHealth);
                            inCombat = 0;
                            goto dungeon;
                        }
                        //Combat loop Ends
                    }
                }
               
            }
        

        }
    
    }

    //Quit Menu
    if (input == quitInput)
    {
        system("cls");
    quit:
        cout << endl;
        renderSystem.printQuitMenu();
        input = ecs.input(InputSystem.getId(), input);
        //Quit
        if (input == quitInput)
            return -1;
        //Return to Menu
        else if (input == returnInput)
            goto menu;
        //Invalid input
        else
        {
            goto invalid;
        }
    }

    //Invalid input
    else
    {
        invalid:
        ecs.invalidInput(InputSystem.getId());
        input = ecs.input(InputSystem.getId(), input);
        goto choice;
    }

    return 0;
}