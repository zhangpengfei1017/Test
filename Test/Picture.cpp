#include "Picture.h"







Picture::Picture(int w, int h, char* d, int i)
{
	Width = w;
	Height = h;
	data = d;
	id = i;
}
Picture::Picture(){
	Width = 0;
	Height = 0;
	data = nullptr;
	id = 0;
}
Picture::~Picture()
{
}

char* Picture::CutOut(int sx, int sy, int ex, int ey) {
	int size = (ex - sx)*(ey - sy);
	char* cut = new char[size];
	int i = 0;
	for (int l = sy; l < ey; l++) {
		for (int r = sx; r < ex; r++) {
			cut[i] = data[l*Width + r];
			i++;
		}
	}
	return cut;
}
