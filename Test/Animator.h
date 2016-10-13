#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;
class Animator
{
public:
	Animator();
	Animator(int w,int h);
	int Width;
	int Height;
	char* imagedata;
	~Animator();
	struct AnimationClip {
		string name;
		int time;//Frames
		int FrameNum;
		char* data;
	};
	int LastUpdateTime=0;
	vector<AnimationClip*> AllAnimationClips;
	int NowPlayingNum=0;
	int FrameCount = 0;
	void ReadAllAnimationClipFile(int AniId);//��ȡ����ͼ���ָ���clip����allclips vector����
	void UpdateAnimation();
};

