#include "Equipment.h"

void Equipment::setWeapon(int idx)
{
	weapon = idx;
}

void Equipment::setArmor(int idx)
{
	armor = idx;
}

void Equipment::setAccessory(int idx)
{
	accessory = idx;
}

int Equipment::getWeapon() const
{
	return weapon;
}

int Equipment::getArmor() const
{
	return armor;
}

int Equipment::getAccessory() const
{
	return accessory;
}

int Equipment::getVitality(int vitality) const
{
	return min(int((vitality + eVitality) * mulVitality), maxVitality);
}

int Equipment::getFocus(int focus) const
{
	return min(int((focus + eFocus) * mulFocus), maxFocus);
}

int Equipment::getSpeed(int speed) const
{
	return min(int((speed + eSpeed) * mulSpeed), maxSpeed);
}

int Equipment::getHitRate(int hitRate) const
{
	return min(int((hitRate + eHitRate) * mulHitRate), maxHitRate);
}

int Equipment::getPAttack(int pAttack) const
{
	return min(int((pAttack + ePAttack) * mulPAttack), maxPAttack);
}

int Equipment::getMAttack(int mAttack) const
{
	return min(int((mAttack + eMAttack) * mulMAttack), maxMAttack);
}

int Equipment::getPDefense(int pDefense) const
{
	return min(int((pDefense + ePDefense) * mulPDefense), maxPDefense);
}

int Equipment::getMDefense(int mDefense) const
{
	return min(int((mDefense + eMDefense) * mulMDefense), maxMDefense);
}

vector<struct skill> Equipment::getSkills()
{

}

int Equipment::useSkill(double rate, int index)
{

}