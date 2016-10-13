#pragma once
#include "winsock2.h"  
#include <iostream>  
#pragma comment(lib, "ws2_32.lib") 
#include <thread>
#include <fstream>
#include "Dungeon.h"
#include "Room.h"
class TcpClient
{
	
public:
	struct aRoom {
		int RoomID = 0;
		int PlayerNum;
		int UIDs[4];
		vector<GameObject*> Players;
		int curDungeon;
		Dungeon AllDungeons[9];
		void loadDungeon() {
			
		}
	};
	TcpClient();
	~TcpClient();
	static SOCKET sHost; //服务器套接字  
	static WSADATA wsd; //WSADATA变量  
	static SOCKADDR_IN servAddr; //服务器地址  
	static char bufSend[10240]; //接收数据缓冲区  
	static char bufRecv[10240];
	static int retVal; //返回值  
	static int UID;
	static Room* mRoom;
	static std::ofstream outfile;
	static int LastConnectTime;
	static bool JoinOk;
	static int RoomIDToJoin;
	//
	static void RecvMsg();
	static int ConnectServer();
	static void SendMsg(int CmdId, int MsgNum,char Msg[]);
	static void CheckMsg(char Msg[]);
};

