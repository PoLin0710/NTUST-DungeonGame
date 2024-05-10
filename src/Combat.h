#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "Role.h"
#include "Entity.h"
#include <set>
#include <comip.h>

class Combat
{
private:
	vector<Entity*> roles;
	vector<Entity*> enemys;
	vector<Entity*> movingOrder;
	int round;
public:
	Combat(vector<Role*>, vector<Entity*>);
	~Combat();
	bool update();
	bool useItem(Entity*);
	void start();
};

#endif //_COMBAT_H_
