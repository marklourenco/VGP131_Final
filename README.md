## Simple RPG in C++ With ECS
### Made by [Mark Lourenco](https://github.com/marklourenco), [Morgan Chin Tang](https://github.com/MorganChinTang) and [Narda Limon](https://github.com/Narda05)

#### Overview
This is a text-based-game we made for school while studying the Entity-Component-System (ECS) and C++ language. The goal is to create a fully functional game engine and apply it on a simple game to show it's capabilities. 
We had two weeks to complete this project in June. Our goal is to utilize the ECS and make a fully functional game that lets players fight monsters to complete quests. 

### Description
Players have a health system, and they can also possess skills to attack or heal. 
Player also have an chance to obtain a weapon that increases their attack damage. 

The enemies will have a random damage dealt to player every turn. 

And each quest will be assigning player to kill x amount of certain enemy. 
For example, 

*Quest:*

*Kill 3 Drakes______1/3*

in this case, the player has killed 1 Drake and has 2 more kills yet to complete. 

### Structure
#### **Entity**
- **Player**_Health, Weapon, Damage, Skill Components
- **Quest**_Quest Components
- **Skill**_Skill, Damage Components
- **Enemies**_Health, Damage Components
	- Wyrmling
	- Drake
	- Dragon
- **Weapon**_Damage Components
	- Longsword

#### **Component**
- **Health:**  Stores base health level and changes as receives damage and heal
- **Weapon:**  Stores player attack damage
- **Skill:**  Stores healing values, and special attack damage value
- **Damage:**  Stores the damage that an entity deals
- **Quest:** Stores the quests and the progress

#### **System**
- **Health:**  Player/Enemy health calculation after an attack/skill.
- **Render:**  Change display text accordingly.
- **Input:**  Player chooses their action.
- **Quest:**   Quest status changes as enemies are defeated.
- **Combat:**   Any calculations relating to combat such as, damage, healing etc.


### Notice
This game is not yet complete. We are still working on it! 

### License 
Our game cannot be used, reproduced, or modified for any non-commercial nor commercial use. 