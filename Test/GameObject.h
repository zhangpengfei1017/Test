#pragma once
#include "Picture.h"
#include <string>
#include <vector>
#include "Animator.h"
class GameObject
{
public:
	GameObject();
	GameObject(int assetid, string name, string tag, int posX,int posY,int posZ,bool ia);
	GameObject(int assetid, string name, string tag, int posX, int posY, int posZ, int width,int height,bool ia);
	~GameObject();
	int PosX;
	int PosY;
	int PosZ;
	int maxHp=500;
	int curHp=500;
	int maxMp=500;
	int curMp=500;
	int attack;
	bool isActive;
	int minX;
	int maxX;
	int direction;
	string name="";
	string tag="";
	int assetid;
	Animator* amt;
	int Width;
	int Height;
	void MoveTo(int x, int y, int z);
	void MoveBy(int x, int y, int z);
	void Turn(int dir);


	//static 
	static GameObject* FindWithName(string name);
	static GameObject* FindWithTag(string tag);
	static void Destroy(GameObject *go);
	static bool ComparePosZ(GameObject* a, GameObject* b);
};

