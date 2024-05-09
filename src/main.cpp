﻿#include "Entity.h"
#include "Role.h"

int main()
{
	srand(time(NULL));
	Role* man1 = new Role("Role1"), * man2 = new Role("Role2"), * man3 = new Role(("Role3"));
	Entity* man4 = new Entity("Player4"), * man5 = new Entity("Player5"), * man6 = new Entity("Player6");
	std::vector<Entity*> Ent = { man4, man5,man6 };
	std::vector<Entity*> rol = { man1, man2,man3 };
	man1->update();
	man2->update();
	man3->update();
	man4->update();
	man5->update();
	man6->update();

	man1->printInfo();
	man1->printBag();


	man4->useSkill(0, Ent, rol);
	man1->printInfo();
	man1->useItem(ITEM_IDX::IGODSBEARD, 13);
	man1->printInfo();
	man1->printBag();
	man1->useSkill(0, rol, Ent);
	man1->useSkill(0, rol, Ent);
	man4->printInfo();
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
