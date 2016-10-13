#pragma once
#include "UIObject.h"

using std::string;
class UILabel :
	public UIObject
{
public:
	UILabel();
	UILabel(UIObject* uo);
	UILabel(string name,int x,int y,string t);
	~UILabel();
	char* Text;

	void SetText(string t);
};

