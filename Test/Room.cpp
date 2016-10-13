#include "Room.h"
#include "GameController.h"


Room::Room()
{
}


Room::~Room()
{
}

void Room::loadDungeon(int id) {
	//put the players at the start postion
	GameController::AllLevels[9]->GameObjectInLevel.clear();
	for (int i = 0; i < PlayerNum; i++) {
		GameController::AllLevels[9]->GameObjectInLevel.push_back(Players[i]);
	}
	curDungeon = id;
	for (int i = 0; i < AllDungeons[id].monnum; i++) {
		if (AllDungeons[id].Monsters[i]->curHp > 0) {
			//add into scene
			GameController::AllLevels[9]->GameObjectInLevel.push_back(AllDungeons[id].Monsters[i]);
		}
	}
	
	//add monsters in the scene
}
