#ifndef CHACKS_H
#define CHACKS_H
#define WIN32_LEAN_AND_MEAN


#include <d3d9.h>
#include <d3dx9.h>
#include "d3dManager_Hack.h"
#include "cStats.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

struct addresses 
{
	BYTE nopOne;
	BYTE nopTwo[2];
	BYTE nopThree[3];
	BYTE nopFour[4];
	BYTE nopFive[5];
	BYTE nopSix[6];

	DWORD dwInGame;
	DWORD dwNoRecoilAddress;
	DWORD dwNoFogAddress;
	DWORD dwNoFlashAddress;
	DWORD dwNametagOneAddress;
	DWORD dwNametagTwoAddress;
	DWORD dwNametagThreeAddress;
	DWORD dwLaserAddress;

	DWORD dwNoRecoilProtect;
	DWORD dwNoFogProtect;
	DWORD dwNoFlashProtect;
	DWORD dwNametagOneProtect;
	DWORD dwNametagTwoProtect;
	DWORD dwNametagThreeProtect;
	DWORD dwLaserProtect;

	BYTE noRecoilOn[2];
	BYTE noFogOn[2];
	BYTE noFlashOn[2];
	BYTE laserOn[2];

	BYTE nametagOneOriginal[6];
	BYTE nametagTwoOriginal[2];
	BYTE nametagThreeOriginal[6];
	BYTE noRecoilOriginal[2];
	BYTE noFogOriginal[2];
	BYTE noFlashOriginal[2];
	BYTE laserOriginal[2];

	addresses()
	{
		nopOne = 0x90;

		nopTwo[0] = 0x90;
		nopTwo[1] = 0x90;

		nopThree[0] = 0x90;
		nopThree[1] = 0x90;
		nopThree[2] = 0x90;

		nopFour[0] = 0x90;
		nopFour[1] = 0x90;
		nopFour[2] = 0x90;
		nopFour[3] = 0x90;

		nopFive[0] = 0x90;
		nopFive[1] = 0x90;
		nopFive[2] = 0x90;
		nopFive[3] = 0x90;
		nopFive[4] = 0x90;

		nopSix[0] = 0x90;
		nopSix[1] = 0x90;
		nopSix[2] = 0x90;
		nopSix[3] = 0x90;
		nopSix[4] = 0x90;
		nopSix[5] = 0x90;

		dwInGame = 0x0074E35C;
		dwNoRecoilAddress = 0x457CCF;
		dwNoFogAddress = 0x63DB0D;
		dwNoFlashAddress = 0x451FB9;
		dwNametagOneAddress = 0x42E1AC;
		dwNametagTwoAddress = 0x42E1CE;
		dwNametagThreeAddress = 0x42E18F;
		dwLaserAddress = 0x456E78;

		noRecoilOn[0] = 0x75;
		noRecoilOn[1] = 0x12;

		noFogOn[0] = 0x74;
		noFogOn[1] = 0x20;

		noFlashOn[0] = 0x75;
		noFlashOn[1] = 0x29;

		laserOn[0] = 0x74;
		laserOn[1] = 0x04;

		nametagOneOriginal[0] = 0x0F;
		nametagOneOriginal[1] = 0x85;
		nametagOneOriginal[2] = 0xCE;
		nametagOneOriginal[3] = 0x00;
		nametagOneOriginal[4] = 0x00;
		nametagOneOriginal[5] = 0x00;

		nametagTwoOriginal[0] = 0x74;
		nametagTwoOriginal[1] = 0x25;

		nametagThreeOriginal[0] = 0x0F;
		nametagThreeOriginal[1] = 0x84;
		nametagThreeOriginal[2] = 0xEB;
		nametagThreeOriginal[3] = 0x00;
		nametagThreeOriginal[4] = 0x00;
		nametagThreeOriginal[5] = 0x00;

		noRecoilOriginal[0] = 0x74;
		noRecoilOriginal[1] = 0x12;

		noFogOriginal[0] = 0x75;
		noFogOriginal[1] = 0x20;

		noFlashOriginal[0] = 0x74;
		noFlashOriginal[1] = 0x29;

		laserOriginal[0] = 0x75;
		laserOriginal[1] = 0x04;
	}
};

struct cHacks
{
	bool aimbot, smoothAim, aimCheck;
	bool nametags, distance, bBoxes, className, grenade;
	bool xHair, laser, chams, statsbox;
	bool recoil, fog, smoke, flash;
	bool rapidFire;
	bool origSet;

	addresses addys;

	cHacks();
	~cHacks();

	void nametagsOn();
	void laserOn();
	void noRecoil();
	void noFog();
	void noSmoke();
	void noFlash();
	void drawStatsBox(d3dManager &manager);
	void disableProtect();
	void enableProtect();
};

#endif