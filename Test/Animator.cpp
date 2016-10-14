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

void Animator::StartPlay(string name)
{
	for (int i = 0; i < AllAnimationClips.size(); i++) {
		if (AllAnimationClips[i]->name == name) {
			NowPlayingNum = i;
			LastUpdateTime = 99999;
			FrameCount = 0;
		}
	}
}

void Animator::ContinuePlay(string name)
{
	for (int i = 0; i < AllAnimationClips.size(); i++) {
		if (AllAnimationClips[i]->name == name) {
			NowPlayingNum = i;
		}
	}
}

void Animator::ReadAllAnimationClipFile(int AniId) {
	{
		AnimationClip* ac = new AnimationClip();
		ac->FrameNum = 1;
		ac->name = "idle";
		ac->time = 125;
		ac->isLoop = true;
		int size = Width*Height*ac->FrameNum;
		ac->data = ScreenGenerator::allasset[AniId].CutOut(0, 0, Width*ac->FrameNum, Height);
		AllAnimationClips.push_back(ac); }
	{
		AnimationClip* ac = new AnimationClip();
		ac->FrameNum = 8;
		ac->name = "walk";
		ac->time = 75;
		ac->isLoop = true;
		int size = Width*Height*ac->FrameNum;
		ac->data = ScreenGenerator::allasset[AniId].CutOut(0, 0, Width*ac->FrameNum, Height);
		//ac->data = ScreenGenerator::allasset[AniId].CutOut(0, 0, 600, 75);
		AllAnimationClips.push_back(ac); }
	{
		AnimationClip* ac = new AnimationClip();
		ac->FrameNum = 8;
		ac->name = "jump";
		ac->time = 75;
		ac->isLoop = false;
		int size = Width*Height*ac->FrameNum;
		ac->data = ScreenGenerator::allasset[AniId].CutOut(0, Height, Width*ac->FrameNum, Height*2);
		AllAnimationClips.push_back(ac); }
	{
		AnimationClip* ac = new AnimationClip();
		ac->FrameNum = 8;
		ac->name = "attack1";
		ac->time = 75;
		ac->isLoop = false;
		int size = Width*Height*ac->FrameNum;
		ac->data = ScreenGenerator::allasset[AniId].CutOut(0, Height*2, Width*ac->FrameNum, Height * 3);
		AllAnimationClips.push_back(ac); }
	{
		AnimationClip* ac = new AnimationClip();
		ac->FrameNum = 8;
		ac->name = "attack2";
		ac->time = 75;
		ac->isLoop = false;
		int size = Width*Height*ac->FrameNum;
		ac->data = ScreenGenerator::allasset[AniId].CutOut(0, Height*3, Width*ac->FrameNum, Height * 4);
		AllAnimationClips.push_back(ac); }

}

void Animator::UpdateAnimation() {
	LastUpdateTime += Time::deltaTime*1000;

	if (LastUpdateTime > AllAnimationClips[NowPlayingNum]->time) {
		int count = 0;
		for (int l = 0; l < Height; l++) {
			for (int r = FrameCount*Width; r < ((FrameCount + 1)*Width); r++) {				
				imagedata[count] = (AllAnimationClips[NowPlayingNum])->data[l * Width*AllAnimationClips[NowPlayingNum]->FrameNum + r];
				count++;
			}
		}
		LastUpdateTime = 0;
		FrameCount++;
		if (!AllAnimationClips[NowPlayingNum]->isLoop&&FrameCount == AllAnimationClips[NowPlayingNum]->FrameNum) {
			StartPlay("idle");
			return;
		}
		FrameCount = FrameCount%AllAnimationClips[NowPlayingNum]->FrameNum;
	}
}

string Animator::getCurrentState()
{
	return AllAnimationClips[NowPlayingNum]->name;
}


