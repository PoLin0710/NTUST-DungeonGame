/***********************************************************************
 * File: Combat.h
 * Author:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: 2024-05-20
 * Editor:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: 2024-05-20
 * Description: The Combat class facilitates the management and execution of combat scenarios within the game,
 *				handling interactions between roles and enemies during battles
***********************************************************************/
#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "Role.h"
#include "Entity.h"
#include "IO.h"
#include <set>
#include <comip.h>


class Combat
{
private:
	// Declare
	vector<Entity*> roles;
	vector<Entity*> enemys;

	//Save output
	map<Entity*, Position> outputXY;

	//store turn
	vector<Entity*> movingOrder;

	//declare Round
	int round;
public:
	//Constructor
	Combat(vector<Role*>, vector<Entity*>);

	//Destructor
	~Combat();

	//update combat
	bool update();

	//useItem
	bool useItem(Entity*);

	//combat start
	void start();
};

#endif //_COMBAT_H_
