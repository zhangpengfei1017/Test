#pragma once
#include "UIObject.h"
class UIList :
	public UIObject
{
public:
	UIList();
	~UIList();
	int NextRow=0;
	vector<UIObject*> ItemInList;	
	UIObject* AddItem(UIObject* obj);
};

