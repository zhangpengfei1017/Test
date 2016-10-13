#include "UIProgressBar.h"



UIProgressBar::UIProgressBar()
{
}

UIProgressBar::UIProgressBar(string name,int posx,int posy,int width,int height,char color)
{
	this->name = name;
	Width = width;
	oriWidth = Width;
	Height = height;
	PosX = posx;
	PosY = posy;
	data = new char[Width*Height];
	for (int i = 0; i < Width*Height; i++) {
		data[i] = color;
	}
	Value = 100;
}


UIProgressBar::~UIProgressBar()
{
}

void UIProgressBar::SetValue(int v) {
	Value = v<0?0:v>100?100:v;
	//float percent = ((float)Value) / ((float)100);
	Width = ((float)Value) / 100 * oriWidth;
	return;
}
