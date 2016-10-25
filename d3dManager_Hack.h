#ifndef D3DMANAGER_H
#define D3DMANAGER_H
#define WIN32_LEAN_AND_MEAN
//#define DEBUGMODE



#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;

#define ReleaseCom(x){if(x){x->Release(); x = NULL;}}

//Colors
#define black D3DCOLOR_ARGB(255, NULL, NULL, NULL)
#define red D3DCOLOR_ARGB(255, 255, NULL, NULL)
#define green D3DCOLOR_ARGB(255, NULL, 255, NULL)
#define blue D3DCOLOR_ARGB(255, NULL, NULL, 255)
#define white D3DCOLOR_ARGB(255, 255, 255, 255)
#define gray D3DCOLOR_ARGB(255, 184, 184, 184)

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)



class d3dManager
{
private:
	LPDIRECT3DDEVICE9 gameDevice;
	LPD3DXLINE mLine;
	LPD3DXFONT mFont;
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	D3DVIEWPORT9 mViewport;

	LPDIRECT3DTEXTURE9 pTexRed;
	LPDIRECT3DTEXTURE9 pTexGreen;
	LPDIRECT3DTEXTURE9 pTexBlue;
	LPDIRECT3DTEXTURE9 pTexYellow;

	LPDIRECT3DPIXELSHADER9 shadeRed;
	LPDIRECT3DPIXELSHADER9 shadeGreen;
	LPDIRECT3DPIXELSHADER9 shadeBlue;
	LPDIRECT3DPIXELSHADER9 shadeYellow;

	ofstream outFile;

	struct CUSTOMVERTEX
	{
		float x, y, z, rhw;

		DWORD diffuse;
	};

public:
	d3dManager();
	~d3dManager();

	void initHook(LPDIRECT3DDEVICE9 *pDevice);
	void generateShader();
	void generateTexture();
	void drawRectOutline(float x, float y, float length, float width, float thickness, D3DCOLOR color);
	void drawShadedRect(float x, float y, float length, float width, D3DCOLOR color);
	void drawXhair(D3DCOLOR color);
	void drawString(LPCSTR text, float x, float y, float length, float width, D3DCOLOR color, bool calcRect);
	float getClientWidth();
	float getClientHeight();
	void prereset();
	void postreset();

	LPDIRECT3DTEXTURE9 getTexture(char *color);
	LPDIRECT3DPIXELSHADER9 getShader(char *color);
};

#endif