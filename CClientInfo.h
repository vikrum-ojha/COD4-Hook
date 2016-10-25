#ifndef CCLIENTINFO
#define CCLIENTINFO

#include <Windows.h>

class CClientInfo
{
public:
	DWORD infoValid; //0x0000  
	__int32 ClientNum; //0x0004  
	char ID0268BD00[4]; //0x0008  
	char PlayerName[16]; //0x000C  
	__int32 iTeam; //0x001C  
	__int32 iTeam2; //0x0020  
	__int32 ID02683D10; //0x0024  
	__int32 ID02683D90; //0x0028  
	__int32 ID02683D80; //0x002C  
	__int32 ID026D5248; //0x0030  
	char unknown52[16]; //0x0034
	char bodyModel[30]; //0x0044  
	char headModel[64]; //0x0062  
	char weapModel[64]; //0x00A2  
	char weaponModel[26]; //0x00E2  
	char unknown252[320]; //0x00FC
	char model[64]; //0x023C  
	char unknown636[284]; //0x027C
	float X; //0x0398  
	float Y; //0x039C  
	float Z; //0x03A0  
	char unknown932[8]; //0x03A4
	float yaw; //0x03AC  
	float roll; //0x03B0  
	float pitch; //0x03B4  
	char unknown952[208]; //0x03B8
	int shooting; //0x0488  
	char unknown1164[4]; //0x048C
	int zoomed; //0x0490  
	char unknown1172[56]; //0x0494
}; //0x4CC( size=1228 )		

extern CClientInfo *cClientInfo;

#endif