#include "Entity.h"

int main()
{
	Entity man1, * man2 = new Entity, * man3 = new Entity;
	std::vector<Entity*> Ent = { man2 };
	std::vector<Entity*> rol = { man3 };
	man1.update();
	std::cout << "Player1\n";
	man1.printInfo();
	std::cout << "\n";
	man1.useSkill(0, rol, Ent);
	man1.printInfo();
}
