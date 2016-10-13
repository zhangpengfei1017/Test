#include "TcpClient.h"
#include "Header.h"
#include<chrono>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include "Input.h"
#include "Time.h"
#include "GameObject.h"
#include "GameController.h"
#include "UILabel.h"
#include <windows.h> 
//







//
using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CHAR_INFO* chiBuffer;
COORD coordBufSize = { 720,160 };
COORD coordBufCoord = { 0,0 };
SMALL_RECT srctWriteRect = { 0,0,720,160 };
HANDLE hNewScreenBuffer;
ofstream outfile("output.txt", ios::in | ios::trunc);
 int LastFrameTime;
int FramesCount = 0;
float deltaTime = 0;
void Start() {
	ScreenGenerator::init();
	GameController::LevelInit();
	Input::Init();		
	Time::init();
	SetWindow();
	
}
void Update() {
	UpdateScreen();
	if (GameController::curLevel->ID == 0) {
		if (Input::GetKey(0x20)) {//space to connect
			GameController::LoadLevel(1);
			return;
		}

	}
	if (GameController::curLevel->ID == 1) {
		int i = TcpClient::ConnectServer();
		if (i == 0) {
			GameController::LoadLevel(2);
			return;
		}
		else if (i == -1) {
			GameController::LoadLevel(3);
			return;
		}
	}
	if (GameController::curLevel->ID == 2) {
		Sleep(1000);
		GameController::LoadLevel(4);
		return;
	}
	if (GameController::curLevel->ID == 3) {
		Sleep(1000);
		GameController::LoadLevel(0);
		return;
	}
	
	if (GameController::curLevel->ID == 6) { //failed to join
		Sleep(1000);
		GameController::LoadLevel(4);
	}
	if (GameController::curLevel->ID == 7) { //succeed to join
											 
		if (Input::GetKeyDown(0x1B)) {//ESC to return hall
			TcpClient::SendMsg(5, 0, nullptr);
			GameController::LoadLevel(4);
		}
		if (Input::GetKeyDown(0x0D)) {//ENTER to start
			TcpClient::SendMsg(6, 0, nullptr);
		}
	}
	if (GameController::curLevel->ID == 5) { //wait to join room
		Sleep(1000);
		if (TcpClient::JoinOk) {
			GameController::LoadLevel(7);
		}
		else {
			GameController::LoadLevel(6);
		}

	}
	if (GameController::curLevel->ID == 4) {
		//进入大厅 只做心跳测试
		if (Input::GetKeyDown(0x43)) {//C create
			GameController::LoadLevel(5);			
			TcpClient::SendMsg(2, 0, nullptr);
		}
		if (Input::GetKeyDown(0x4A)) {//J join
			GameController::LoadLevel(5);
			TcpClient::SendMsg(3, TcpClient::RoomIDToJoin, nullptr);
		}
		if (Input::GetKeyDown(0x1B)) {//ESC to exit hall
			TcpClient::SendMsg(4, 0, nullptr);
			GameController::LoadLevel(0);
		}
		if (Input::GetKeyDown(0x26)) {//UP
			TcpClient::RoomIDToJoin = (TcpClient::RoomIDToJoin + 1) < 0 ? 0 : (TcpClient::RoomIDToJoin + 1);
			GameController::curLevel->UI_mutex.lock();
			((UILabel*)GameController::AllLevels[4]->UIInLevel[6])->SetText(std::to_string(TcpClient::RoomIDToJoin));
			GameController::curLevel->UI_mutex.unlock();
		}
		if (Input::GetKeyDown(0x28)) {//DOWN
			TcpClient::RoomIDToJoin = (TcpClient::RoomIDToJoin - 1) < 0 ? 0 : (TcpClient::RoomIDToJoin - 1);
			GameController::curLevel->UI_mutex.lock();
			((UILabel*)GameController::AllLevels[4]->UIInLevel[6])->SetText(std::to_string(TcpClient::RoomIDToJoin));
			GameController::curLevel->UI_mutex.unlock();
		}
	}
	if (GameController::curLevel->ID == 8) {// lost connection
		if (Input::GetKeyDown(0x1B)) {//ESC TO MENU
			GameController::LoadLevel(0);
		}
	}
	if (GameController::curLevel->ID >= 9) {
		GameController::curLevel->UI_mutex.lock();
		((UILabel*)GameController::AllLevels[9]->UIInLevel[0])->SetText(std::to_string(Time::FPS)+"  "+std::to_string(((Time::FramesCount/((float)Time::NowTime())/1000.0))));
		GameController::curLevel->UI_mutex.unlock();

		for (int i = 0; i < GameController::curLevel->GameObjectInLevel.size(); i++) {
			GameController::curLevel->GameObjectInLevel[i]->amt->UpdateAnimation();
		}
		
		GameObject* player = GameObject::FindWithName("Player");
		if (player != nullptr) {
			if (Input::GetKey(0x57)) {
				player->MoveBy(0, 0, -1);
			}//w
			if (Input::GetKey(0x53)) {
				player->MoveBy(0, 0, 1);
			}//s
			if (Input::GetKey(0x41)) {
				player->MoveBy(-1, 0, 0);
			}//a
			if (Input::GetKey(0x44)) {
				player->MoveBy(1, 0, 0);
			}//d
			if (Input::GetKeyDown(0x43)) {
				TcpClient::mRoom->curDungeon=(TcpClient::mRoom->curDungeon+1)%9;
				TcpClient::mRoom->loadDungeon(TcpClient::mRoom->curDungeon);
			}//c
		}
		
	}
	
}







int main() {
	Start();
	while (1) {
		if (Time::UpdateTime()) {
			Update();
		}
	}
}
void SetWindow() {
	chiBuffer = ScreenGenerator::NextScreen();
	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);
	SetConsoleActiveScreenBuffer(hNewScreenBuffer);
	SetConsoleScreenBufferSize(hNewScreenBuffer, coordBufSize);
	WriteConsoleOutput(
		hNewScreenBuffer, // screen buffer to write to 
		chiBuffer,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&srctWriteRect);  // dest. screen buffer rectangle 
	SMALL_RECT rc = { 0,0, 720 - 1, 160 - 1 }; // 重置窗口位置和大小
	SetConsoleWindowInfo(hNewScreenBuffer, TRUE, &rc);
}
void UpdateScreen() {
	auto t1 = chrono::high_resolution_clock::now();
	chiBuffer = ScreenGenerator::NextScreen();
	auto t2 = chrono::high_resolution_clock::now();
	WriteConsoleOutput(
		hNewScreenBuffer, // screen buffer to write to 
		chiBuffer,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&srctWriteRect);  // dest. screen buffer rectangle 
	auto t3 = chrono::high_resolution_clock::now();
	auto delta1 = chrono::duration<float>(t2 - t1).count();
	auto delta2 = chrono::duration<float>(t3 - t2).count();
}

