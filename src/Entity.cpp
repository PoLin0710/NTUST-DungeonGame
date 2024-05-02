#include "Entity.h"

Entity::Entity()
{
	srand(time(NULL));

	this->initVitality = 30 + rand() % 15; // Range [30,45)
	this->initFocus = 3;
	this->initSpeed = 30 + rand() % 25; // Range [30,55)
	this->initAccuracy = 40 + rand() % 20; // Range [40,60)
	this->initPAttack = 5 + rand() % 16; // Range [5,15]
	this->initMAttack = 5 + rand() % 16; // Range [5,15]
	this->initPDefense = rand() % 21; // Range [0,20]
	this->initMDefense = rand() % 21; // Range [0,20]

	this->Vitality = this->initVitality;
	this->Focus = this->initFocus;
	this->Speed = this->initSpeed;
	this->Accuracy = this->initAccuracy;
	this->PAttack = this->initPAttack;
	this->MAttack = this->initMAttack;
	this->PDefense = this->initPDefense;
	this->MDefense = this->initMDefense;
}

Entity::~Entity()
{
}

void Entity::setVitality(int Vitality) {
	this->initVitality = Vitality;
}

void Entity::setFocus(int Focus) {
	this->initFocus = Focus;
}

void Entity::setSpeed(int Speed) {
	this->initSpeed = Speed;
}

void Entity::setAccuracy(int Accuracy) {
	this->initAccuracy = Accuracy;
}

void Entity::setPAttack(int PAttack) {
	this->initPAttack = PAttack;
}

void Entity::setMAttack(int MAttack) {
	this->initMAttack = MAttack;
}

void Entity::setPDefense(int PDefense) {
	this->initPDefense = PDefense;
}

void Entity::setMDefense(int MDefense) {
	this->initMDefense = MDefense;
}

void Entity::setWeapon(Equipment Weapon) {
	this->Weapon = Weapon;
}

void Entity::setArmor(Equipment Armor) {
	this->Armor = Armor;
}

void Entity::setAccessory(Equipment Accessory) {
	this->Accessory = Accessory;
}

int Entity::getVitality() const {
	return initVitality;
}

int Entity::getFocus() const {
	return initFocus;
}

int Entity::getSpeed() const {
	return initSpeed;
}

int Entity::getAccuracy() const {
	return initAccuracy;
}

int Entity::getPAttack() const {
	return initPAttack;
}

int Entity::getMAttack() const {
	return initMAttack;
}

int Entity::getPDefense() const {
	return initPDefense;
}

int Entity::getMDefense() const {
	return initMDefense;
}

Equipment Entity::getWeapon() const {
	return Weapon;
}

Equipment Entity::getArmor() const {
	return Armor;
}

Equipment Entity::getAccessory() const {
	return Accessory;
}

double Entity::RolltheDice(int diceNum, int successNum)
{
	double successRate = 0;

	for (int i = 0; i < diceNum; i++)
	{
		if (i < successNum)
		{
			successRate++;
		}
		else
		{
			int Roll = rand() % 100 + 1;

			if (Roll >= Accuracy)
			{
				successRate++;
			}
		}
	}

	return successRate / diceNum;
}

void Entity::printInfo()
{
	std::cout << "Vitality is: " << initVitality << std::endl;
	std::cout << "Focus is: " << initFocus << std::endl;
	std::cout << "Speed is: " << initSpeed << std::endl;
	std::cout << "Accuracy is: " << initAccuracy << std::endl;
	std::cout << "PAttack is: " << initPAttack << std::endl;
	std::cout << "MAttack is: " << initMAttack << std::endl;
	std::cout << "PDefense is: " << initPDefense << std::endl;
	std::cout << "MDefense is: " << initMDefense << std::endl;
}

