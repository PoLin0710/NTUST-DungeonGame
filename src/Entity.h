/***********************************************************************
 * File: Entity.h
 * Author:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: 2024-05-21
 * Editor:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: 2024-05-21
 * Description: Definition of the Entity class, representing characters and enemies in the game.
***********************************************************************/
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

//Declare Entity type
enum ENTITY_TYPE {
	ROLE = 0,
	ENEMY = 1
};

//Declare Entity class
class Entity {
private:
	//Declare info
	int type;
	std::string name;
	char eicon;

	//Declare initValue
	int initVitality;
	int initFocus;
	int initSpeed;
	int initHitRate;
	int initPAttack;
	int initMAttack;
	int initPDefense;
	int initMDefense;

	//Declare maxValue
	int maxVitality;
	int maxFocus;
	int maxSpeed;
	int maxHitRate;
	int maxPAttack;
	int maxMAttack;
	int maxPDefense;
	int maxMDefense;

	//Declare currentValue
	int curVitality;
	int curFocus;
	int curSpeed;
	int curHitRate;
	int curPAttack;
	int curMAttack;
	int curPDefense;
	int curMDefense;

	//Flee state
	bool isFlee;

	//Equipment attribute
	Equipment equipment;

	//active skills attribute
	std::vector<skill> activeSkills;
	std::vector<int> activeSkillsCD;

	//passive skills attribute
	std::vector<skill> passiveSkills;
	std::vector<int> passiveSkillsCD;

	//bbuff attribute
	std::vector<Buff::Buff> buffs;
public:
	//Constructor
	Entity(std::string, int, char);

	//Destructor
	virtual~Entity();

	//Set function
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

	//Get  function
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

	//Use function
	double RolltheDice(int, int, int, int);
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

	//Output function
	void printInfo(int, int);
	void printSkills(int, int);

	//info attribute
	int turn;
	Position ePos;
};

#endif // _ENTITY_H_
