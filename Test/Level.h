#pragma once
#include "GameObject.h"
#include <vector>
#include "UIObject.h"
#include <mutex>
class Level
{
public:
	int ID;
	int assetnum;
	int LevelLength;
	int BackgroundId;
	vector<GameObject*> GameObjectInLevel;
	vector<UIObject*> UIInLevel;
	std::mutex UI_mutex;



};

