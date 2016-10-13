#pragma once
#include <vector>
#include"GameObject.h"
#include"Dungeon.h"
class Room
{
public:
	Room();
	~Room();
	int RoomID = 0;
	int PlayerNum;
	int UIDs[4];
	vector<GameObject*> Players;
	int curDungeon;
	Dungeon AllDungeons[9];
	void loadDungeon(int id);
};

