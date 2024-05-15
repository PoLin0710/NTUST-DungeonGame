#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Equipment.h"
#include "Position.h"
#include "Buff.h"
#include "List.h"
#include "IO.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <map>

enum ENTITY_TYPE {
	ROLE = 0,
	ENEMY = 1
};

class Entity {
private:
	int type;
	std::string name;
	char eicon;

	int initVitality;
	int initFocus;
	int initSpeed;
	int initHitRate;
	int initPAttack;
	int initMAttack;
	int initPDefense;
	int initMDefense;

	int maxVitality;
	int maxFocus;
	int maxSpeed;
	int maxHitRate;
	int maxPAttack;
	int maxMAttack;
	int maxPDefense;
	int maxMDefense;

	int curVitality;
	int curFocus;
	int curSpeed;
	int curHitRate;
	int curPAttack;
	int curMAttack;
	int curPDefense;
	int curMDefense;

	bool isFlee;

	Equipment equipment;

	std::vector<skill> activeSkills;
	std::vector<int> activeSkillsCD;

	std::vector<skill> passiveSkills;
	std::vector<int> passiveSkillsCD;

	std::vector<Buff::Buff> buffs;
public:
	Entity(std::string, int, char);
	virtual~Entity();

	void setVitality(int);
	void setFocus(int);
	void setSpeed(int);
	void setHitRate(int);
	void setPAttack(int);
	void setMAttack(int);
	void setPDefense(int);
	void setMDefense(int);
	void setWeapon(int);
	void setArmor(int);
	void setAccessory(int);
	void setIcon(char);

	string getName() const;
	int getVitality() const;
	int getFocus() const;
	int getSpeed();
	int getHitRate() const;
	int getPAttack() const;
	int getMAttack() const;
	int getPDefense() const;
	int getMDefense() const;
	int getWeapon() const;
	int getArmor() const;
	int getAccessory() const;
	int getType() const;
	int getActiveSkillSize() const;
	bool getIsFlee() const;
	std::vector<skill> getActiveSkills() const;
	bool isDizziness();
	char getIcon()const;

	double RolltheDice(int, int);
	void update();
	void combatUpdate();
	bool useSkill(int, std::vector<Entity*>, std::vector<Entity*>);
	int useFocus(int);
	void heal(int, std::vector<Entity*>);
	void attack(int, int, int, std::vector<Entity*>);
	void insertBuff(int);
	std::vector<Entity*> chooseEntitys(int, std::vector<Entity*>);
	bool turnStart();
	void turnEnd();
	bool findSkills(SKILL_IDX);
	bool findBuffs(Buff::BUFF_IDX);


	void printInfo(int, int);
	void printSkills(int, int);

	int turn;
	Position ePos;
};

#endif // _ENTITY_H_
