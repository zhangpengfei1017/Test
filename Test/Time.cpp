#include "Time.h"
#include <ctime>


Time::Time()
{
}


Time::~Time()
{
}
void Time::init() {
	LastFrameTime = 0;
	FramesCount = 0;
	deltaTime = 0;
}
bool Time::UpdateTime() {
	if ((clock() - LastFrameTime) > 0) {
		deltaTime = (((float)(clock() - LastFrameTime)) / 1000);
		LastFrameTime = (int)clock();
		FramesCount++;
		FPS = ((float)(1 / deltaTime));
		return(true);
	}
	else {
		return(false);
	}
}
int Time::NowTime() {
	return(clock());
}
int Time::LastFrameTime;
int Time::FPS;
int Time::FramesCount;
float Time::deltaTime;