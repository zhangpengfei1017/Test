#include "UIList.h"



UIList::UIList()
{
	data = new char[Width*Height];
	for (int i = 0; i < Width*Height;i++) {
		data[i] = 'T';
	}
}


UIList::~UIList()
{
}

