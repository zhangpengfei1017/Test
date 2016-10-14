#include "TcpClient.h"
#include "GameController.h"
#include "Time.h"
#include "UILabel.h"
#include "UIProgressBar.h"
#include <string>
#include <mutex>
struct HeadPackage_C00 {
	int UID;
	int CmdID;
};
struct JoinRoom_C03 {
	int RoomID;
};

struct PlayerInfo_C08 {
	int posx;
	int posy;
	int posz;
};

struct PlayerAttack_C09 {
	int posx;
	int posy;
	int posz;
	int skill;
	int direction;
};

//
// server struct below
struct HeadPackage_S00 {
	int UID;
	int CmdID;
};
struct HallInfo_S01 {
	int RoomNum;
};
struct RoomInHall_S01 {
	int RoomId;
	int PlayerNum;
	int P1UID;
};
struct RoomInfo_S02 {
	int RoomId;
};
struct RoomCurentInfo_S05 {
	int RoomID;
	int UIDs[4];
	int PlayerNum;
};

struct GameStartInfoHead_S06 {
	int playernum;
};
struct GameStartPlayerInfo_S06 {
	int UID;
};
struct GameStartDungeonInfo_S06 {
	int maptype;
	int monnum;
};
struct GameStartMonsterInfo_S06 {
	int MonID;
	int type;
	int PosX;
	int PosY;
	int PosZ;
	int maxHp;
	int curHp;
	int attack;
};
struct GameInfoHead_S08 {
	int playernum;
	int monsternum;
};
struct GamePlayerInfo_S08 {
	int UID;
	int posx;
	int posy;
	int posz;
	int maxhp;
	int curhp;
	int maxmp;
	int curmp;
};
struct GameMonsterInfo_S08 {
	int ID;
	int posx;
	int posy;
	int posz;
	int maxhp;
	int curhp;
};
void TcpClient::CheckMsg(char Msg[]) {
	HeadPackage_S00 hp;
	int BufPos = 0;
	memset(&hp, 0, sizeof(hp));
	memcpy(&hp, Msg, sizeof(hp));
	BufPos += sizeof(hp);
	switch (hp.CmdID)
	{
	case 0:// receive the fist package from server to get the UID
		UID = hp.UID;
		GameController::curLevel->UI_mutex.lock();
		((UILabel*)GameController::AllLevels[4]->UIInLevel[0])->SetText("UID:" + std::to_string(UID));
		GameController::curLevel->UI_mutex.unlock();
		break;
	case 1:// receive the heart beat request from server
		HallInfo_S01 hi;
		memset(&hi, 0, sizeof(hi));
		memcpy(&hi, Msg + BufPos, sizeof(hi));
		BufPos += sizeof(hi);
		GameController::curLevel->UI_mutex.lock();
		((UILabel*)GameController::AllLevels[4]->UIInLevel[1])->SetText("");
		((UILabel*)GameController::AllLevels[4]->UIInLevel[2])->SetText("");
		((UILabel*)GameController::AllLevels[4]->UIInLevel[3])->SetText("");
		((UILabel*)GameController::AllLevels[4]->UIInLevel[4])->SetText("");
		GameController::curLevel->UI_mutex.unlock();
		for (int i = 0; i < hi.RoomNum; i++) {
			RoomInHall_S01 ri;
			memset(&ri, 0, sizeof(ri));
			memcpy(&ri, Msg + BufPos, sizeof(ri));
			BufPos += sizeof(ri);
			//add hall infomation to UI
			GameController::curLevel->UI_mutex.lock();
			((UILabel*)GameController::AllLevels[4]->UIInLevel[i + 1])->SetText(std::to_string(ri.RoomId)+" UID:"+std::to_string(ri.P1UID)+"   Players:"+std::to_string(ri.PlayerNum)+"/4");
			GameController::curLevel->UI_mutex.unlock();
			//
		}
		SendMsg(1, 0, nullptr);
		break;
	case 2:// receive the room# from server
	{RoomInfo_S02 ri;
	memset(&ri, 0, sizeof(ri));
	memcpy(&ri, Msg + BufPos, sizeof(ri));
	BufPos += sizeof(ri);
	mRoom->RoomID = ri.RoomId;
	GameController::curLevel->UI_mutex.lock();
	((UILabel*)GameController::AllLevels[7]->UIInLevel[0])->SetText("Room Id:"+std::to_string(ri.RoomId));
	GameController::curLevel->UI_mutex.unlock();
	}
		
		break;
	case 3:// succeed to join
		JoinOk = true;
		break;
		//jumplevel;
	case 4://fail to join
		JoinOk = false;
		break;
		//jumplevel;
	case 5://update the room inside info
	{RoomCurentInfo_S05 rci;
	memset(&rci, 0, sizeof(rci));
	memcpy(&rci, Msg + BufPos, sizeof(rci));
	BufPos += sizeof(rci);
	mRoom->RoomID = rci.RoomID;
	mRoom->PlayerNum = rci.PlayerNum;
	string str = "Room Id:";
	str += std::to_string(rci.RoomID);
	str += "  Player#:";
	str += std::to_string(rci.PlayerNum);
	for (int i = 0; i < 4; i++) {
		((UILabel*)GameController::AllLevels[7]->UIInLevel[i + 1])->isActive = false;
		((UILabel*)GameController::AllLevels[7]->UIInLevel[i + 5])->SetText("");
	}
	for (int i = 0; i < mRoom->PlayerNum; i++) {
		mRoom->UIDs[i] = rci.UIDs[i];
		(GameController::AllLevels[7]->UIInLevel[i + 1])->isActive = true;
		((UILabel*)GameController::AllLevels[7]->UIInLevel[i+5])->SetText("UID:"+std::to_string(rci.UIDs[i]));
	}
	if (GameController::curLevel->ID == 7) {
		
		UILabel* uil=(UILabel*)UIObject::FindUIWithName("Room_ID");
		
		if (uil != nullptr) {
			uil->SetText(str);
		}
		else {
			break;
		}
		
	}	
	SendMsg(1, 0, nullptr); }
		break;
	case 6://receive the init game info
		GameStartInfoHead_S06 gsih;
		memset(&gsih, 0, sizeof(gsih));
		memcpy(&gsih, Msg + BufPos, sizeof(gsih));
		BufPos += sizeof(gsih);
		for (int i = 0; i < gsih.playernum; i++) {
			GameStartPlayerInfo_S06 gspi;
			memset(&gspi, 0, sizeof(gspi));
			memcpy(&gspi, Msg + BufPos, sizeof(gspi));
			BufPos += sizeof(gspi);
			if (gspi.UID == UID) {
				GameObject*p = new GameObject(15, "Player", "", 60, 0, 20,43,75, true);
				mRoom->Players.push_back(p);
			}
			else {
				GameObject*p = new GameObject(15, std::to_string(gspi.UID), "", 60, 0, 20,43,75, true);
				mRoom->Players.push_back(p);
			}
			
		}
		for (int i = 0; i < 9; i++) {
			GameStartDungeonInfo_S06 gsdi;
			memset(&gsdi, 0, sizeof(gsdi));
			memcpy(&gsdi, Msg + BufPos, sizeof(gsdi));
			BufPos += sizeof(gsdi);
			mRoom->curDungeon = 0;
			mRoom->AllDungeons[i].monnum = gsdi.monnum;
			mRoom->AllDungeons[i].type = gsdi.maptype;
			for (int j = 0; j < gsdi.monnum; j++) {
				GameStartMonsterInfo_S06 gsmi;
				memset(&gsmi, 0, sizeof(gsmi));
				memcpy(&gsmi, Msg + BufPos, sizeof(gsmi));
				//save in room info
				GameObject* mon = new GameObject(gsmi.type, to_string(gsmi.MonID), "Monster",gsmi.PosX, gsmi.PosY, gsmi.PosZ,43,75,true);
				mon->maxHp = gsmi.maxHp;
				mon->curHp = gsmi.curHp;
				mon->attack = gsmi.attack;
				mRoom->AllDungeons[i].Monsters.push_back(mon);
				//
				BufPos += sizeof(gsmi);// has received init dungeon info, need a class to store all the infomation
			}
		}
		SendMsg(7, 0, nullptr);//ready;
		break;
	case 7:
		mRoom->loadDungeon(0);
		Sleep(1000);		
		GameController::LoadLevel(9);
		break;
	case 8: {//receive game info
		GameInfoHead_S08 gih;
		memset(&gih, 0, sizeof(gih));
		memcpy(&gih, Msg + BufPos, sizeof(gih));
		BufPos += sizeof(gih);
		for (int i = 0; i < gih.playernum; i++) {
			GamePlayerInfo_S08 gpi;
			memset(&gpi, 0, sizeof(gpi));
			memcpy(&gpi, Msg + BufPos, sizeof(gpi));
			BufPos += sizeof(gpi);
			if (gpi.UID != UID) {
				string n = std::to_string(gpi.UID);
				GameObject* p = GameObject::FindWithName(n);
				if (p != nullptr) {
					p->MoveTo(gpi.posx, gpi.posy, gpi.posz);
				}
				
			}
		}
		for (int i = 0; i < gih.monsternum; i++) {
			GameMonsterInfo_S08 gmi;
			memset(&gmi, 0, sizeof(gmi));
			memcpy(&gmi, Msg + BufPos, sizeof(gmi));
			BufPos += sizeof(gmi);
			for (int j = 0; j < mRoom->AllDungeons[mRoom->curDungeon].Monsters.size(); j++) {
				GameObject* m = mRoom->AllDungeons[mRoom->curDungeon].Monsters[j];
				if (m->name == to_string(gmi.ID)) {
					m->MoveTo(gmi.posx, gmi.posy, gmi.posz);
					m->curHp = gmi.curhp;
					m->maxHp = gmi.maxhp;	
					if (gmi.ID == 0) {
						((UIProgressBar*)GameController::AllLevels[9]->UIInLevel[1])->SetValue(gmi.curhp * 100 / gmi.maxhp);
					}
				}
			}			
		}
		SendMsg(1, 0, nullptr);
		break;
	}
	default:
		break;
	}
	LastConnectTime = Time::NowTime();
}
void TcpClient::SendMsg(int CmdId,int MsgNum, char MsgChar[]) {
	HeadPackage_C00 hp = { UID,CmdId };
	int BufPos = 0;
	memset(bufSend, 0, 10240);
	memcpy(bufSend, &hp, sizeof(hp));
	BufPos += sizeof(hp);
	switch (CmdId)
	{
	case 1://心跳回应 00.
		break;
	case 2://建立房间 00.
		
		break;
	case 3://加入房间 00 03.
		JoinRoom_C03 jr;
		jr.RoomID = MsgNum;
		memcpy(bufSend + BufPos, &jr, sizeof(jr));
		BufPos += sizeof(jr);
		break;
	case 4://退出大厅 .
		break;
	case 5://退出房间 .
		break;
	case 6://开始游戏 .
		break;
	case 7://init ready for game scene;
		break;
	case 8://return movement to server;
	{PlayerInfo_C08 pi;
	GameObject* p = GameObject::FindWithName("Player");
	pi.posx = p->PosX;
	pi.posy = p->PosY;
	pi.posz = p->PosZ;
	memcpy(bufSend + BufPos, &pi, sizeof(pi));
	BufPos += sizeof(pi);
	break; }
	case 9://attack
	{
		PlayerAttack_C09 pa;
		GameObject*p = GameObject::FindWithName("Player");
		pa.posx = p->PosX;
		pa.posy = p->PosY;
		pa.posz = p->PosZ;
		pa.direction = p->direction;
		pa.skill = 0;
		memcpy(bufSend + BufPos, &pa, sizeof(pa));
		BufPos += sizeof(pa);
		break;
	}
	default:
		break;
	}
	send(sHost, bufSend, BufPos, 0);
	//outfile << "发送了" << CmdId << std::endl;
}
TcpClient::TcpClient()
{
}
TcpClient::~TcpClient()
{
}
int TcpClient::ConnectServer() {
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		std::cout << "WSAStartup failed!" << std::endl;
		return -1;
	}
	//创建套接字  	
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//	ioctlsocket(sHost, FIONBIO, &mode);
	if (INVALID_SOCKET == sHost)
	{
		std::cout << "socket failed!" << std::endl;
		WSACleanup();//释放套接字资源  
		return  -1;
	}

	//设置服务器地址  
	servAddr.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = inet_addr("47.89.187.20");
	servAddr.sin_addr.s_addr = inet_addr("192.168.0.13");
	servAddr.sin_port = htons((short)4999);
	int nServAddlen = sizeof(servAddr);
	//连接服务器  	
	int attempt = 0;
	while (true) {
		Sleep(1000);
		retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
		if (SOCKET_ERROR != retVal)
		{
			break;
		}
		else {
			attempt++;
		}
		if (attempt >= 30) {
			return(-1);
		}
	}
	std::thread RecvThread(&RecvMsg);
	LastConnectTime = Time::NowTime();
	RecvThread.detach();
	return 0;
}
void TcpClient::RecvMsg() {
	while (true)
	{
		ZeroMemory(bufRecv, 10240);
		if (recv(sHost, bufRecv, 10240, 0) != SOCKET_ERROR) {
			CheckMsg(bufRecv);
		}
		//退出  
		if ((Time::NowTime() - LastConnectTime) > 10000) {
			GameController::LoadLevel(8);
			break;
		}
	}
		closesocket(sHost); //关闭套接字  
		WSACleanup(); //释放套接字资源  
}

///

SOCKET TcpClient::sHost; //服务器套接字  
WSADATA TcpClient::wsd; //WSADATA变量  
SOCKADDR_IN TcpClient::servAddr; //服务器地址  
char TcpClient::bufSend[10240]; //接收数据缓冲区  
char TcpClient::bufRecv[10240];
int TcpClient::retVal; //返回值  
int TcpClient::UID;//UID for this client, default is 0;
Room* TcpClient::mRoom=new Room();
int TcpClient::LastConnectTime;
bool TcpClient::JoinOk;
int TcpClient::RoomIDToJoin = 0;
