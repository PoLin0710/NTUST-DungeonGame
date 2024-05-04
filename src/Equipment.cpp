#include "Equipment.h"

void Equipment::setWeapon(int)
{

}

void Equipment::setArmor(int)
{

}

void Equipment::setAccessory(int)
{

}

int Equipment::getWeapon() const
{

}
int Equipment::getArmor() const
{

}
int Equipment::getAccessory() const
{

}

int Equipment::getVitality(int vitality) const
{
	return (vitality + eVitality) * mulVitality;
}

int Equipment::getFocus(int Focus) const
{
	return (Focus + eFocus) * mulFocus;
}

int Equipment::getSpeed(int Speed) const
{
	return (Speed + eSpeed) * mulSpeed;
}

int Equipment::getHitRate(int HitRate) const
{
	return (HitRate + eHitRate) * mulHitRate;
}

int Equipment::getPAttack(int PAttack) const
{
	return (PAttack + ePAttack) * mulPAttack;
}

int Equipment::getMAttack(int MAttack) const
{
	return (MAttack + eMAttack) * mulMAttack;
}

int Equipment::getPDefense(int PDefense) const
{
	return (PDefense + ePDefense) * mulPDefense;
}

int Equipment::getMDefense(int MDefense) const
{
	return (MDefense + eMDefense) * mulMDefense;
}

vector<struct skill> Equipment::getSkills()
{

}

int Equipment::useSkill(double rate, int index)
{

}