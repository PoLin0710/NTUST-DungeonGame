#include "Entity.h"

int main()
{
	srand(time(NULL));
	Entity* man1 = new Entity("Player1"), * man2 = new Entity("Player2"), * man3 = new Entity(("Player3")), * man4 = new Entity("Player4");
	std::vector<Entity*> Ent = { man2, man4 };
	std::vector<Entity*> rol = { man1, man3 };
	man1->update();
	man2->update();
	man3->update();
	man4->update();
	man1->printInfo();
	std::cout << "\n";
	int useidx;
	std::cout << "Choose skills: ";
	std::cin >> useidx;
	man1->useSkill(useidx, rol, Ent);
	man2->printInfo();
	std::cout << "\n\n";
	std::cout << "Choose skills: ";
	std::cin >> useidx;
	man2->useSkill(useidx, Ent, rol);

	for (auto i : Ent)
	{
		i->printInfo();
	}

	for (auto i : rol)
	{
		i->printInfo();
	}

}
