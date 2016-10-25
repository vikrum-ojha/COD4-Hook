#include "cHacks.h"
#ifdef DEBUGMODE
#include <iostream>
#endif

cHacks::cHacks()
{
}
cHacks::~cHacks()
{
}
void cHacks::nametagsOn()
{
	if (nametags)
	{
		VirtualProtect((LPVOID) addys.dwNametagOneAddress, 6, PAGE_EXECUTE_READWRITE, &addys.dwNametagOneProtect);
		VirtualProtect((LPVOID) addys.dwNametagTwoAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwNametagTwoProtect);
		VirtualProtect((LPVOID) addys.dwNametagThreeAddress, 6, PAGE_EXECUTE_READWRITE, &addys.dwNametagThreeProtect);

		memcpy((LPVOID)addys.dwNametagOneAddress, addys.nopSix, 6);
		memcpy((LPVOID)addys.dwNametagTwoAddress, addys.nopTwo, 2);
		memcpy((LPVOID)addys.dwNametagThreeAddress, addys.nopSix, 6);

		VirtualProtect((LPVOID) addys.dwNametagOneAddress, 6, addys.dwNametagOneProtect, &addys.dwNametagOneProtect);
		VirtualProtect((LPVOID) addys.dwNametagTwoAddress, 2, addys.dwNametagTwoProtect, &addys.dwNametagTwoProtect);
		VirtualProtect((LPVOID) addys.dwNametagThreeAddress, 6, addys.dwNametagThreeProtect, &addys.dwNametagThreeProtect);
	}
	else
	{
		VirtualProtect((LPVOID) addys.dwNametagOneAddress, 6, PAGE_EXECUTE_READWRITE, &addys.dwNametagOneProtect);
		VirtualProtect((LPVOID) addys.dwNametagTwoAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwNametagTwoProtect);
		VirtualProtect((LPVOID) addys.dwNametagThreeAddress, 6, PAGE_EXECUTE_READWRITE, &addys.dwNametagThreeProtect);

		memcpy((LPVOID)addys.dwNametagOneAddress, addys.nametagOneOriginal, 6);
		memcpy((LPVOID)addys.dwNametagTwoAddress, addys.nametagTwoOriginal, 2);
		memcpy((LPVOID)addys.dwNametagThreeAddress, addys.nametagThreeOriginal, 6);

		VirtualProtect((LPVOID) addys.dwNametagOneAddress, 6, addys.dwNametagOneProtect, &addys.dwNametagOneProtect);
		VirtualProtect((LPVOID) addys.dwNametagTwoAddress, 2, addys.dwNametagTwoProtect, &addys.dwNametagTwoProtect);
		VirtualProtect((LPVOID) addys.dwNametagThreeAddress, 6, addys.dwNametagThreeProtect, &addys.dwNametagThreeProtect);
	}
}

void cHacks::laserOn()
{
	if (laser)
	{
		VirtualProtect((LPVOID) addys.dwLaserAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwLaserProtect);
		memcpy((LPVOID)addys.dwLaserAddress, addys.laserOn, 2);
		VirtualProtect((LPVOID) addys.dwLaserAddress, 2, addys.dwLaserProtect, &addys.dwLaserProtect);
	}
	else
	{
		VirtualProtect((LPVOID) addys.dwLaserAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwLaserProtect);
		memcpy((LPVOID)addys.dwLaserAddress, addys.laserOriginal, 2);
		VirtualProtect((LPVOID) addys.dwLaserAddress, 2, addys.dwLaserProtect, &addys.dwLaserProtect);
	}
}
void cHacks::noRecoil()
{
	if (recoil)
	{
		VirtualProtect((LPVOID) addys.dwNoRecoilAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwNoRecoilProtect);
		memcpy((LPVOID)addys.dwNoRecoilAddress, addys.noRecoilOn, 2);
		VirtualProtect((LPVOID) addys.dwNoRecoilAddress, 2, addys.dwNoRecoilProtect, &addys.dwNoRecoilProtect);
	}
	else
	{

		VirtualProtect((LPVOID) addys.dwNoRecoilAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwNoRecoilProtect);
		memcpy((LPVOID)addys.dwNoRecoilAddress, addys.noRecoilOriginal, 2);
		VirtualProtect((LPVOID) addys.dwNoRecoilAddress, 2, addys.dwNoRecoilProtect, &addys.dwNoRecoilProtect);
	}
}
void cHacks::noFog()
{
	if (fog)
	{
		VirtualProtect((LPVOID) addys.dwNoFogAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwNoFogProtect);
		memcpy((LPVOID)addys.dwNoFogAddress, addys.noFogOn, 2);
		VirtualProtect((LPVOID) addys.dwNoFogAddress, 2, addys.dwNoFogProtect, &addys.dwNoFogProtect);
	}
	else
	{
		VirtualProtect((LPVOID) addys.dwNoFogAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwNoFogProtect);
		memcpy((LPVOID)addys.dwNoFogAddress, addys.noFogOriginal, 2);
		VirtualProtect((LPVOID) addys.dwNoFogAddress, 2, addys.dwNoFogProtect, &addys.dwNoFogProtect);
	}
}
void cHacks::noSmoke()
{
}
void cHacks::noFlash()
{
	if (flash)
	{
		VirtualProtect((LPVOID) addys.dwNoFlashAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwNoFlashProtect);
		memcpy((LPVOID)addys.dwNoFlashAddress, addys.noFlashOn, 2);
		VirtualProtect((LPVOID) addys.dwNoFlashAddress, 2, addys.dwNoFlashProtect, &addys.dwNoFlashProtect);
	}
	else
	{
		VirtualProtect((LPVOID) addys.dwNoFlashAddress, 2, PAGE_EXECUTE_READWRITE, &addys.dwNoFlashProtect);
		memcpy((LPVOID)addys.dwNoFlashAddress, addys.noFlashOriginal, 2);
		VirtualProtect((LPVOID) addys.dwNoFlashAddress, 2, addys.dwNoFlashProtect, &addys.dwNoFlashProtect);
	}
}