#pragma once
#include "UIObject.h"
class UIProgressBar :
	public UIObject
{
public:
	UIProgressBar();
	UIProgressBar(string name,int posx,int posy,int width,int height,char color);
	~UIProgressBar();
	int Value;
	int oriWidth;
	void SetValue(int v);
};

