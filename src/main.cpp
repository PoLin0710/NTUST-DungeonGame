#include "Entity.h"

int main()
{
	srand(time(NULL));
	Entity *man1 = new Entity, * man2 = new Entity, * man3 = new Entity, * man4 = new Entity;
	std::vector<Entity*> Ent = { man2, man4 };
	std::vector<Entity*> rol = { man1, man3 };
	man1->update();
	man2->update();
	man3->update();
	man4->update();
	std::cout << "Player1\n";
	man1->printInfo();
	std::cout << "\n";
	int useidx;
	std::cout << "Choose skills: ";
	std::cin >> useidx;
	man1->useSkill(useidx, rol, Ent);
	std::cout << "Player2\n";
	man2->printInfo();
	std::cout << "\n\n";
	std::cout << "Choose skills: ";
	std::cin >> useidx;
	man2->useSkill(useidx, Ent, rol);
	std::cout << "\nPlayer2\n";
	man2->printInfo();
	std::cout << "\nPlayer1\n";
	man1->printInfo();

}
