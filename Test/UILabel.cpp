#include "UILabel.h"
UILabel::UILabel()
{
	Width = 0;
	Height = 7;
}
UILabel::UILabel(UIObject* uo)
{
}


UILabel::UILabel(string name,int x, int y, string t) {
	Width = 0;
	Height = 7;
	this->name = name;
	PosX = x;
	PosY = y;
	Text = nullptr;
	this->data = nullptr;
	SetText(t);
}
UILabel::~UILabel()
{
}

void UILabel::SetText(string t) {
	if (Text != nullptr) {
		delete[] Text;
	}
	if (data != nullptr) {
		delete[] data;
	}
	Width = t.size() * 6;
	Text = new char[t.size()];
	data = new char[t.size() * 42];
	for (int i = 0; i < t.size(); i++) {
		Text[i] = t[i];
		char* NextChar= ScreenGenerator::GetCharData(Text[i]);
		int count = 0;
		for (int l = 0; l < 7; l++) {
			for (int r = i * 6; r < (i * 6 + 6); r++) {
				data[l * 6*t.size() + r] = NextChar[count];
				count++;
			}
		}
		delete[] NextChar;
	}
	
}
