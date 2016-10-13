#pragma once
#include <vector>
#include"GameObject.h"
class Dungeon
{
public:
	struct Monster {
		int MonID;
		int type;
		int PosX;
		int PosY;
		int PosZ;
		int maxHp;
		int curHp;
		int attack;
	};
	Dungeon();
	~Dungeon();
	int type;
	int monnum;
	vector<GameObject*> Monsters;
};

