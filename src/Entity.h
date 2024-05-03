#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Equipment.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

class Entity {
private:
	int initVitality;
	int initFocus;
	int initSpeed;
	int initHitRate;
	int initPAttack;
	int initMAttack;
	int initPDefense;
	int initMDefense;

	int vitality;
	int focus;
	int speed;
	int hitRate;
	int pAttack;
	int mAttack;
	int pDefense;
	int mDefense;

	Equipment equipment;

	std::vector<std::string> skills;
public:
	Entity();
	~Entity();

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

	int getVitality() const;
	int getFocus() const;
	int getSpeed() const;
	int getHitRate() const;
	int getPAttack() const;
	int getMAttack() const;
	int getPDefense() const;
	int getMDefense() const;
	int getWeapon() const;
	int getArmor() const;
	int getAccessory() const;

	double RolltheDice(int, int);

	void printInfo();
};

#endif // _ENTITY_H_
