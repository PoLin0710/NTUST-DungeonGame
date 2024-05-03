#include "Entity.h"

Entity::Entity()
{
	srand(time(NULL));

	this->initVitality = 30 + rand() % 15; // Range [30,45)
	this->initFocus = 3;
	this->initSpeed = 30 + rand() % 25; // Range [30,55)
	this->initHitRate = 40 + rand() % 20; // Range [40,60)
	this->initPAttack = 5 + rand() % 16; // Range [5,15]
	this->initMAttack = 5 + rand() % 16; // Range [5,15]
	this->initPDefense = rand() % 21; // Range [0,20]
	this->initMDefense = rand() % 21; // Range [0,20]

	this->equipment.setWeapon(WEAPON_IDX::WEAPON_NONE);
	this->equipment.setArmor(ARMOR_IDX::ARMOR_NONE);
	this->equipment.setAccessory(ACCESSORY_IDX::ACCESSORY_NONE);

	this->vitality = equipment.getVitality(this->initVitality);
	this->focus = equipment.getFocus(this->initFocus);
	this->speed = equipment.getSpeed(this->initSpeed);
	this->hitRate = equipment.getHitRate(this->initHitRate);
	this->pAttack = equipment.getPAttack(this->initPAttack);
	this->mAttack = equipment.getMAttack(this->initMAttack);
	this->pDefense = equipment.getPDefense(this->initPDefense);
	this->mDefense = equipment.getMDefense(this->initMDefense);

}

Entity::~Entity()
{
}

void Entity::setVitality(int vitality) {
	this->vitality = vitality;
}

void Entity::setFocus(int focus) {
	this->focus = focus;
}

void Entity::setSpeed(int speed) {
	this->speed = speed;
}

void Entity::setHitRate(int hitRate) {
	this->hitRate = hitRate;
}

void Entity::setPAttack(int pAttack) {
	this->pAttack = pAttack;
}

void Entity::setMAttack(int mAttack) {
	this->mAttack = mAttack;
}

void Entity::setPDefense(int pDefense) {
	this->pDefense = pDefense;
}

void Entity::setMDefense(int mDefense) {
	this->mDefense = mDefense;
}

void Entity::setWeapon(int weapon) {
	this->equipment.setWeapon(weapon);
}

void Entity::setArmor(int armor) {
	this->equipment.setArmor(armor);
}

void Entity::setAccessory(int accessory) {
	this->equipment.setAccessory(accessory);
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

int Entity::getHitRate() const {
	return initHitRate;
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

int Entity::getWeapon() const {
	return equipment.getWeapon();
}

int Entity::getArmor() const {
	return equipment.getArmor();
}

int Entity::getAccessory() const {
	return equipment.getAccessory();
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

			if (Roll >= hitRate)
			{
				successRate++;
			}
		}
	}

	return successRate / diceNum;
}

void Entity::printInfo()
{
	std::cout << "Vitality is: " << vitality << std::endl;
	std::cout << "Focus is: " << focus << std::endl;
	std::cout << "Speed is: " << speed << std::endl;
	std::cout << "HitRate is: " << hitRate << std::endl;
	std::cout << "PAttack is: " << pAttack << std::endl;
	std::cout << "MAttack is: " << mAttack << std::endl;
	std::cout << "PDefense is: " << pDefense << std::endl;
	std::cout << "MDefense is: " << mDefense << std::endl;
	std::cout << "Weapon is: " << equipment.getWeapon() << std::endl;
	std::cout << "Armor is: " << equipment.getArmor() << std::endl;
	std::cout << "Accessory is: " << equipment.getAccessory() << std::endl;
}

