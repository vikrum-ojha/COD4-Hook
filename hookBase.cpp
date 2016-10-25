#include "hookBase.h"
#include "d3dManager_Hack.h"
#include "cMenu.h"
#include "cStats.h"

#ifdef DEBUGMODE
#include <iostream>
using namespace std;
#endif

PDWORD EndsceneAddress;
PDWORD PresentAddress;
PDWORD SetStreamSourceAddress;
PDWORD DrawIndexedPrimitiveAddress;
PDWORD ResetAddress;
int *IsInGame = (int *)IsInGameAddress;

PUINT HCMode = (PUINT)0x74E378;

origBeginscene oBeginscene;
origEndscene oEndscene;
origPresent oPresent;
origSetStreamSource oSetStreamSource;
origDrawIndexedPrimitive oDrawIndexedPrimitive;	
origReset oReset;

d3dManager d3dObject;

UINT m_Stride;

cMenu menu;

bool init = false;
bool exited = false;
bool reset = false;

HRESULT WINAPI mBeginscene(LPDIRECT3DDEVICE9 pDevice)
{
	if (reset)
	{
		d3dObject.postreset();

		reset = false;
	}

	return oBeginscene(pDevice);
}
HRESULT WINAPI mEndscene(LPDIRECT3DDEVICE9 pDevice)
{
	//setStartingStats();

	//Draw ESP here.


	if (!init)
	{
		d3dObject.initHook(&pDevice);

		init = true;
	}
	/*if (*menu.hObject.addys.dwIsInGame != NULL)
	{*/

	//Handle menu stuff in it's own function.  Clean this up for a single call.
	menu.drawBaseRows(d3dObject);
	menu.drawMenuLeaflets(d3dObject);
	menu.drawStatus(d3dObject);

	menu.setStatus();
	//Memory hacking.
	menu.hackThread(d3dObject);
	if (*IsInGame != NULL)
	{

		if (menu.visuals[vCrosshair].status == 1)
		{
			d3dObject.drawXhair(red);
		}
	}

	d3dObject.prereset();
	//}



	return oEndscene(pDevice);
}
HRESULT WINAPI mPresent(LPDIRECT3DDEVICE9 pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{	
	return oPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
HRESULT WINAPI mSetStreamSource(LPDIRECT3DDEVICE9 pDevice, UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes, UINT Stride)
{
	if (StreamNumber == 0)
	{
		m_Stride = Stride;
	}

	return oSetStreamSource(pDevice, StreamNumber, pStreamData, OffsetInBytes, Stride);
}
HRESULT WINAPI mDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
	if (*IsInGame != NULL)
	{
		//No Smoke
		if (NumVertices == 16384)
		{
			if (menu.removables[rSmoke].status == 1)
			{
				return NULL;
			}
		}

		//No Rain
		if ((m_Stride == 20) && (NumVertices == 4096) && (PrimitiveCount == 2048))
		{
			if (menu.removables[rRain].status == 1)
			{
				return NULL;
			}
		}
		//No Sniper Scope
		//Add bool for scoped in to prevent some "HC Mode" effects from kicking in.  Eg. No grenade counters/engine Xhair.
		if ((m_Stride == 32) && (*HCMode > 0) && ((NumVertices == 12) || ((PrimitiveCount == 6) || (PrimitiveCount == 8))))
		{
			if (menu.removables[rSniperScope].status == 1)
			{
				return NULL;
			}
		}
		//Asus Walls
		if (m_Stride == 44)
		{
			if (menu.visuals[vAsusWalls].status == 1)
			{
				pDevice->SetRenderState(D3DRS_SRCBLEND, 3);
				pDevice->SetRenderState(D3DRS_DESTBLEND, 4);
				pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			}
		}
		//No Grass.Bugged...need more primitives.
		//if ((PrimitiveCount == 190) || (PrimitiveCount == 210) || (PrimitiveCount == 90) || (PrimitiveCount == 100) || (PrimitiveCount == 110) || (PrimitiveCount == 160) || (PrimitiveCount == 180) || (PrimitiveCount == 200) || (PrimitiveCount == 240) || (PrimitiveCount == 270) || (PrimitiveCount == 294) || (PrimitiveCount == 330) || (PrimitiveCount == 370) || (PrimitiveCount == 462) || (PrimitiveCount == 510) || (PrimitiveCount == 1020) || (PrimitiveCount == 1280))
		//{
		//	//Stopped at 2950

		//	if (menu.removables[6].status == 1)
		//	{
		//		return NULL;
		//	}
		//}

		/////////////////////////////////////////////////////////

		//Chams

		if (m_Stride == 32)
		{
			LPDIRECT3DPIXELSHADER9 gameShader;
			LPDIRECT3DBASETEXTURE9 tex;
			DWORD dwOldState = D3DZB_TRUE;

			pDevice->GetPixelShader(&gameShader);
			pDevice->GetTexture(NULL, &tex);

			if (menu.visuals[vChams].status > 0)
			{
				//d3dObject.generateShader(); -Causes crash when called in DIP but is okay in beginscene...

				if (GoodPlayers)// Change for team for constant color schemes.
				{
					//pDevice->SetTexture(NULL, d3dObject.getTexture("green"));
					if (menu.other[oRenderMode].status == NULL)
					{
						pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
					}
					else if (menu.other[oRenderMode].status == 1)
					{
						pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
					}
					else if (menu.other[oRenderMode].status == 2)
					{
						pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
					}
					pDevice->GetRenderState(D3DRS_ZENABLE, &dwOldState);
					pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
					if (menu.visuals[vChams].status == 2)
					{
						//pDevice->SetTexture(NULL, tex);
						pDevice->SetPixelShader(d3dObject.getShader("yellow"));
					}
					else if (menu.visuals[vChams].status == 1)
					{
						//pDevice->SetPixelShader(gameShader);
						pDevice->SetTexture(NULL, d3dObject.getTexture("yellow"));
					}
					oDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);

					pDevice->SetRenderState(D3DRS_ZENABLE, dwOldState);

					if (menu.visuals[vChams].status == 2)
					{
						pDevice->SetTexture(NULL, tex);
						pDevice->SetPixelShader(d3dObject.getShader("red"));
					}
					else if (menu.visuals[vChams].status == 1)
					{
						//pDevice->SetPixelShader(gameShader);
						pDevice->SetTexture(NULL, d3dObject.getTexture("red"));
					}
					//pDevice->SetPixelShader(d3dObject.getShader("red"));
					//pDevice->SetTexture(NULL, d3dObject.getTexture("red"));

					//oDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
				}
				else if (BadPlayers)
				{
					//pDevice->SetTexture(NULL, d3dObject.getTexture("green"));
					//pDevice->SetTexture(NULL, d3dObject.getTexture("green"));
					if (menu.other[oRenderMode].status == NULL)
					{
						pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
					}
					else if (menu.other[oRenderMode].status == 1)
					{
						pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
					}
					else if (menu.other[oRenderMode].status == 2)
					{
						pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
					}
					pDevice->GetRenderState(D3DRS_ZENABLE, &dwOldState);
					pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
					if (menu.visuals[vChams].status == 2)
					{
						//pDevice->SetTexture(NULL, tex);
						pDevice->SetPixelShader(d3dObject.getShader("blue"));
					}
					else if (menu.visuals[vChams].status == 1)
					{
						//pDevice->SetPixelShader(gameShader);
						pDevice->SetTexture(NULL, d3dObject.getTexture("blue"));
					}
					oDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);

					pDevice->SetRenderState(D3DRS_ZENABLE, dwOldState);

					if (menu.visuals[vChams].status == 2)
					{
						pDevice->SetTexture(NULL, tex);
						pDevice->SetPixelShader(d3dObject.getShader("green"));
					}
					else if (menu.visuals[vChams].status == 1)
					{
						pDevice->SetPixelShader(gameShader);
						pDevice->SetTexture(NULL, d3dObject.getTexture("green"));
					}
					//pDevice->SetPixelShader(d3dObject.getShader("red"));
					//pDevice->SetTexture(NULL, d3dObject.getTexture("red"));

					//oDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
				}
				else if ((!GoodPlayers) || (!BadPlayers))
				{
					pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				}
				else
				{
					pDevice->SetPixelShader(gameShader);
				}

			}
		}
	}

	return oDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
}
HRESULT WINAPI mReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *pPresentationParams)
{
	reset = true;

	return oReset(pDevice, pPresentationParams);
}
void getAddresses()
{
	PDWORD vTable = NULL;

	LPDIRECT3D9 d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	LPDIRECT3DDEVICE9 pDevice;
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;

	d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice);

	vTable = (PDWORD)pDevice;
	vTable = (PDWORD)vTable[0];

	EndsceneAddress = (PDWORD)vTable[42];
	PresentAddress = (PDWORD)vTable[17];
	SetStreamSourceAddress = (PDWORD)vTable[100];
	DrawIndexedPrimitiveAddress = (PDWORD)vTable[82];
	ResetAddress = (PDWORD)vTable[16];

	pDevice->Release();
	d3d9->Release();
	pDevice = NULL;
	d3d9 = NULL;
}
void logAddresses()
{
	ofstream outFile;

	outFile.open("C:\\HookLog.txt", ios::app);

	outFile << "\nBeginning Address Logging...\n";
	outFile << "Endscene: 0x" << EndsceneAddress << "\n";
	outFile << "Endscene(&): 0x" << &EndsceneAddress << "\n";
	outFile << "Present: 0x" << PresentAddress << "\n";
	outFile << "Present(&): 0x" << &PresentAddress << "\n";
	outFile << "SetStreamSource: 0x" << SetStreamSourceAddress << "\n";
	outFile << "SetStreamSource(&): 0x" << &SetStreamSourceAddress << "\n";
	outFile << "End of logging...\n\n";

	outFile.close();
}

DWORD WINAPI hThread()
{
	while (!exited)
	{
		menu.navigate();

		Sleep(25);
	}

	if (exited)
	{
		ExitThread(NULL);
	}

	return NULL;
}
DWORD WINAPI dwThread()
{
	if (exited)
	{
		ExitThread(NULL);
	}

	getAddresses();

#ifdef DEBUGMODE
	logAddresses();
#endif

	oEndscene = (origEndscene)mDetourDef(EndsceneAddress, mEndscene);
	oPresent = (origPresent)mDetourDef(PresentAddress, mPresent);
	oSetStreamSource = (origSetStreamSource)mDetourDef(SetStreamSourceAddress, mSetStreamSource);
	oDrawIndexedPrimitive = (origDrawIndexedPrimitive)mDetourDef(DrawIndexedPrimitiveAddress, mDrawIndexedPrimitive);
	oReset = (origReset)mDetourDef(ResetAddress, mReset);

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&hThread, NULL, NULL, NULL);

	return NULL;
}
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{

#ifdef DEBUGMODE
	ofstream outFile;
#endif
	HANDLE hThreadHandle = NULL;

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hDll);

#ifdef DEBUGMODE

			AllocConsole();
			AttachConsole(GetCurrentProcessId());
			freopen("CON", "w", stdout);

			outFile.open("C:\\HookLog.txt");
			outFile << "Injected.\n";
			outFile.close();
#endif

			hThreadHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&dwThread, NULL, NULL, NULL);
			break;
		}
	case DLL_PROCESS_DETACH:
		{

#ifdef DEBUGMODE
			FreeConsole();

			outFile.open("C:\\HookLog.txt", ios::app);
			outFile << "Detached.\n";
			outFile.close();
#endif
			//Clean up in here.
			exited = true;
			TerminateThread(hThreadHandle, NULL);
			CloseHandle(hThreadHandle);
			ExitThread(NULL);

			break;
		}
	}

	return TRUE;
}