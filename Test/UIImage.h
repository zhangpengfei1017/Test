#pragma once
#include "UIObject.h"
class UIImage :
	public UIObject
{
public:
	UIImage(string n,int aid,int posx,int posy,int w,int h);
	UIImage();
	~UIImage();
	int assetid;
};

