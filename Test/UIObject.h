#pragma once
#include "ScreenGenerator.h"
#include <string>
class UIObject
{
public:
	UIObject();
	~UIObject();
	string name;
	int PosX;
	int PosY;
	int Width;
	int Height;
	char* data;
	bool isActive = true;
	void MoveTo(int x, int y);

	static UIObject* FindUIWithName(string name);
};

