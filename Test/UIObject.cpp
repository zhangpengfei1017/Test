#include "UIObject.h"
#include "GameController.h"


UIObject::UIObject()
{
}


UIObject::~UIObject()
{
}

void UIObject::MoveTo(int x, int y) {
	PosX = x<0?0:x;
	PosY = y<0?0:y;
}


UIObject* UIObject::FindUIWithName(string name) {
	for (int i = 0; i < GameController::curLevel->UIInLevel.size(); i++) {
		if (GameController::curLevel->UIInLevel[i]->name == name){
			return GameController::curLevel->UIInLevel[i];
		}
	}
	return nullptr;	
}