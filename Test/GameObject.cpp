#include "TcpClient.h"
#include "GameObject.h"
#include "ScreenGenerator.h"
#include <algorithm> 
#include "GameController.h"


GameObject::GameObject()
{
}



GameObject::GameObject(int assetid, string name, string tag, int posX, int posY, int posZ, bool ia) {
	this->name = name;
	this->tag = tag;
	this->PosX = posX;
	this->PosY = posY;
	this->PosZ = posZ;
	this->isActive = ia;
	this->assetid=assetid;
	this->amt = new Animator();
	amt->ReadAllAnimationClipFile(assetid);
}
GameObject::GameObject(int assetid, string name, string tag, int posX, int posY, int posZ, int width, int height,bool ia) {
	this->name = name;
	this->tag = tag;
	this->PosX = posX;
	this->PosY = posY;
	this->PosZ = posZ;
	this->Width = width;
	this->Height = height;
	this->isActive = ia;
	this->assetid = assetid;
	this->amt = new Animator(Width,Height);
	amt->ReadAllAnimationClipFile(assetid);
}


GameObject::~GameObject()
{
}
void GameObject::MoveTo(int x, int y, int z) {
	this->PosX = x;
	this->PosY = y;
	this->PosZ = z;
	std::sort(GameController::curLevel->GameObjectInLevel.begin(), GameController::curLevel->GameObjectInLevel.end(), ComparePosZ);
}
void GameObject::MoveBy(int x, int y, int z) {
	minX = Width / 2+10;
	maxX = GameController::curLevel->LevelLength - minX-10;
	this->PosX = this->PosX + x > minX ? this->PosX + x < maxX ? this->PosX + x : maxX : minX;
	this->PosZ = this->PosZ+z<10?10: this->PosZ + z>130?130: this->PosZ + z;
	if (this->PosX -ScreenGenerator::CamPosX< minX) {
		ScreenGenerator::CamMove(x);
	}
	else if (this->PosX - ScreenGenerator::CamPosX > 360 - minX) {
		ScreenGenerator::CamMove(x);
	}
	std::sort(GameController::curLevel->GameObjectInLevel.begin(), GameController::curLevel->GameObjectInLevel.end(), ComparePosZ);
	TcpClient::SendMsg(8, 0, nullptr);

}
void GameObject::Turn() {}



void GameObject::Destroy(GameObject* go) {
	std::vector<GameObject*>::iterator iter = std::find(GameController::curLevel->GameObjectInLevel.begin(), GameController::curLevel->GameObjectInLevel.end(), go);
	GameController::curLevel->GameObjectInLevel.erase(iter);
	delete go;
}
bool GameObject::ComparePosZ(GameObject* a, GameObject* b) {
	return(a->PosZ < b->PosZ);
}

GameObject* GameObject::FindWithName(string name) {
	Level* curLv = GameController::curLevel;
	for (int i = 0; i < curLv->GameObjectInLevel.size(); i++) {
		if (curLv->GameObjectInLevel[i]->name == name) {
			return curLv->GameObjectInLevel[i];
		}
	}
	return nullptr;
}

GameObject* GameObject::FindWithTag(string tag) {
	Level* curLv = GameController::curLevel;
	for (int i = 0; i < curLv->GameObjectInLevel.size(); i++) {
		if (curLv->GameObjectInLevel[i]->tag == tag) {
			return curLv->GameObjectInLevel[i];
		}
	}
	return nullptr;
}

