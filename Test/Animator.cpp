#include "Animator.h"
#include "Time.h"
#include "ScreenGenerator.h"
#include <fstream>
Animator::Animator()
{
}
Animator::Animator(int w,int h)
{
	Width = w;
	Height = h;
	imagedata = new char[w*h];
	memset(imagedata,'T', w*h);
}


Animator::~Animator()
{
}

void Animator::ReadAllAnimationClipFile(int AniId) {
	AnimationClip* ac=new AnimationClip();
	char* clipdata = new char[45000];
	for (int i = 0; i < 45000; i++) {
		clipdata[i] = ScreenGenerator::allasset[AniId].data[i];
	}
	ac->data = clipdata;
	ac->FrameNum = 8;
	ac->name = "walk";
	ac->time = 125;
	AllAnimationClips.push_back(ac);
}
void Animator::UpdateAnimation() {
	LastUpdateTime += Time::deltaTime*1000;

	if (LastUpdateTime > AllAnimationClips[NowPlayingNum]->time) {
		int count = 0;
		for (int l = 0; l < Height; l++) {
			for (int r = FrameCount*Width; r < ((FrameCount + 1)*Width); r++) {				
				imagedata[count] = (AllAnimationClips[NowPlayingNum])->data[l * 600 + r];
				count++;
			}
		}
		LastUpdateTime = 0;
		FrameCount++;
		FrameCount = FrameCount%AllAnimationClips[NowPlayingNum]->FrameNum;
	}
}
