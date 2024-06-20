#ifndef COMPONENTS_H
#define COMPONENTS_H

using namespace std;

struct HealthComponent {
    int hp;

    HealthComponent(int initialHp) : hp(initialHp) {}
};

struct DamageComponent {
    int damage;

    DamageComponent(int initialDamage) : damage(initialDamage) {}
};

// NARDA 2 ------------------
struct LongswordComponent {
	int damage;

	LongswordComponent(int initialDamage) : damage(initialDamage) {}
};

struct HealSkillComponent {
	int heal;

	HealSkillComponent(int initialHeal) : heal(initialHeal) {}
};

struct BashSkillComponent {
	int bash;

	BashSkillComponent(int initialBash) : bash(initialBash) {}
};

struct QuestComponent {
	int quest;

    QuestComponent(int initialQuest) : quest(initialQuest){}

};
struct QuestCompleteComponent {
	int questComplete;

	QuestCompleteComponent(int initialQuestComplete) : questComplete(initialQuestComplete) {}

};


// ------------------

#endif