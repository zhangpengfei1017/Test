#include "GameController.h"
#include "UILabel.h"
#include "UIProgressBar.h"
#include "UIImage.h"


GameController::GameController()
{
}


GameController::~GameController()
{
}

void GameController::LevelInit() {
	//lv00 Start
	Level* lv0 = new Level();
	AllLevels.push_back(lv0);
	LoadLevel(0);
	lv0->BackgroundId = 0;
	lv0->LevelLength = 360;
	lv0->ID = 0;

	//lv01 Connecting
	Level* lv1 = new Level();
	AllLevels.push_back(lv1);
	lv1->BackgroundId = 1;
	lv1->LevelLength = 360;
	lv1->ID = 1;

	//lv02 Connect Successfully
	Level* lv2 = new Level();
	AllLevels.push_back(lv2);
	lv2->BackgroundId = 2;
	lv2->LevelLength = 360;
	lv2->ID = 2;

	//lv03 Connect Unsuccessfully
	Level* lv3 = new Level();
	AllLevels.push_back(lv3);
	lv3->BackgroundId = 3;
	lv3->LevelLength = 360;
	lv3->ID = 3;

	//lv04 Waiting in hall
	Level* lv4 = new Level();
	AllLevels.push_back(lv4);
	lv4->BackgroundId = 4;
	lv4->LevelLength = 360;
	lv4->ID = 4;
	UILabel* ul = new UILabel("UID", 50, 30, "UID:0");
	lv4->UIInLevel.push_back(ul);	
	UILabel* ul1 = new UILabel("Room1", 55, 58, "1  UID:0   Players:3");
	lv4->UIInLevel.push_back(ul1);
	UILabel* ul2 = new UILabel("Room2", 55, 78, "2  UID:0   Players:3");
	lv4->UIInLevel.push_back(ul2);
	UILabel* ul3 = new UILabel("Room3", 55, 98, "3  UID:0   Players:3");
	lv4->UIInLevel.push_back(ul3);
	UILabel* ul4 = new UILabel("Room4", 55, 118, "4  UID:0   Players:3");
	lv4->UIInLevel.push_back(ul4);
	UILabel* ul5 = new UILabel("Title", 50, 45, "ID     Information");
	lv4->UIInLevel.push_back(ul5);
	UILabel* ul6 = new UILabel("RoomID", 240, 72, "0");
	lv4->UIInLevel.push_back(ul6);
	//lv05 connecting to the room
	Level* lv5 = new Level();
	AllLevels.push_back(lv5);
	lv5->BackgroundId = 5;
	lv5->LevelLength = 360;
	lv5->ID = 5;

	//lv05 failed to join room
	Level* lv6 = new Level();
	AllLevels.push_back(lv6);
	lv6->BackgroundId = 6;
	lv6->LevelLength = 360;
	lv6->ID = 6;

	//lv06 Waiting in Room
	Level* lv7 = new Level();
	AllLevels.push_back(lv7);
	lv7->BackgroundId = 7;
	lv7->LevelLength = 360;
	lv7->ID = 7;
	UILabel* ul0 = new UILabel("Room_ID",60, 15, "");//0
	lv7->UIInLevel.push_back(ul0);
	UIImage* p1 = new UIImage("p1", 14, 53, 50, 60, 60);
	p1->isActive = false;
	lv7->UIInLevel.push_back(p1);
	UIImage* p2 = new UIImage("p2", 14, 117, 50, 60, 60);
	p2->isActive = false;
	lv7->UIInLevel.push_back(p2);
	UIImage* p3 = new UIImage("p3", 14, 181, 50, 60, 60);
	p3->isActive = false;
	lv7->UIInLevel.push_back(p3);
	UIImage* p4 = new UIImage("p4", 14, 245, 50, 60, 60);
	p4->isActive = false;
	lv7->UIInLevel.push_back(p4);

	UILabel* p1uid = new UILabel("p1uid", 67, 115 ,"");//5
	lv7->UIInLevel.push_back(p1uid);
	UILabel* p2uid = new UILabel("p2uid", 131, 115, "");
	lv7->UIInLevel.push_back(p2uid);
	UILabel* p3uid = new UILabel("p3uid", 195, 115, "");
	lv7->UIInLevel.push_back(p3uid);
	UILabel* p4uid = new UILabel("p4uid", 259, 115, "");
	lv7->UIInLevel.push_back(p4uid);

	//lv08 lost connection
	Level* lv8 = new Level();
	AllLevels.push_back(lv8);
	lv8->BackgroundId = 8;
	lv8->LevelLength = 360;
	lv8->ID = 8;

	//lv09 Game Scene1
	Level* lv9 = new Level();
	AllLevels.push_back(lv9);
	lv9->BackgroundId = 9;
	lv9->LevelLength = 720;
	lv9->ID = 9;
	UILabel* frame = new UILabel("frame", 20, 20, "");
	UIProgressBar* mon1hp = new UIProgressBar("Hp", 40, 20, 100, 10, '7');
	lv9->UIInLevel.push_back(frame);
	lv9->UIInLevel.push_back(mon1hp);	
}
void GameController::LoadLevel(int lvid) {
	curLevel = AllLevels[lvid];
}





//

vector<Level*> GameController::AllLevels;
Level* GameController::curLevel;