#include "UIImage.h"



UIImage::UIImage()
{
}


UIImage::~UIImage()
{
}

UIImage::UIImage(string n,int aid, int posx, int posy, int w, int h) {
	this->name = n;
	this->PosX = posx;
	this->PosY = posy;
	this->Width = w;
	this->Height = h;
	this->assetid = aid;
	this->data = new char[w*h];
	for (int i = 0; i < (w*h); i++) {
		data[i] = ScreenGenerator::allasset[aid].data[i];
	}
	
}