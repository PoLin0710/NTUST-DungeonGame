#include "Entity.h"

int main()
{
	srand(time(NULL));
	Entity man1, * man2 = new Entity, * man3 = new Entity, * man4 = new Entity;
	std::vector<Entity*> Ent = { man2,man4 };
	std::vector<Entity*> rol = { man3 };
	man1.update();
	man2->update();
	std::cout << "Player1\n";
	man1.printInfo();
	std::cout << "\n";
	man1.useSkill(0, rol, Ent);
	std::cout << "Player2\n";
	man2->printInfo();
	std::cout << "\n\n";
	man2->useSkill(2, Ent, rol);
	std::cout << "\n";
	man2->printInfo();

}
