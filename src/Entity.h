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
	int initAccuracy;
	int initPAttack;
	int initMAttack;
	int initPDefense;
	int initMDefense;

	int Vitality;
	int Focus;
	int Speed;
	int Accuracy;
	int PAttack;
	int MAttack;
	int PDefense;
	int MDefense;

	Equipment Weapon;
	Equipment Armor;
	Equipment Accessory;

	std::vector<std::string> skills;
public:
	Entity();
	~Entity();

	void setVitality(int);
	void setFocus(int);
	void setSpeed(int);
	void setAccuracy(int);
	void setPAttack(int);
	void setMAttack(int);
	void setPDefense(int);
	void setMDefense(int);
	void setWeapon(Equipment);
	void setArmor(Equipment);
	void setAccessory(Equipment);

	int getVitality() const;
	int getFocus() const;
	int getSpeed() const;
	int getAccuracy() const;
	int getPAttack() const;
	int getMAttack() const;
	int getPDefense() const;
	int getMDefense() const;
	Equipment getWeapon() const;
	Equipment getArmor() const;
	Equipment getAccessory() const;

	double RolltheDice(int, int);

	void printInfo();
};

#endif // _ENTITY_H_
