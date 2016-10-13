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
	static SOCKET sHost; //�������׽���  
	static WSADATA wsd; //WSADATA����  
	static SOCKADDR_IN servAddr; //��������ַ  
	static char bufSend[10240]; //�������ݻ�����  
	static char bufRecv[10240];
	static int retVal; //����ֵ  
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

