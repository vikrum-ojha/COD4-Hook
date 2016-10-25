#include "d3dManager_Hack.h"

d3dManager::d3dManager(): gameDevice(NULL), mLine(NULL), mFont(NULL)
{
}
d3dManager::~d3dManager()
{
	ReleaseCom(mLine);
	ReleaseCom(mFont);
	ReleaseCom(vertexBuffer);
	ReleaseCom(pTexGreen);
	ReleaseCom(pTexRed);
	ReleaseCom(pTexBlue);
	ReleaseCom(pTexYellow);
	ReleaseCom(shadeRed);
	ReleaseCom(shadeBlue);
	ReleaseCom(shadeGreen);
	ReleaseCom(shadeYellow);

#ifdef DEBUGMODE
	FreeConsole();
#endif
}
void d3dManager::initHook(LPDIRECT3DDEVICE9 *pDevice)
{

#ifdef DEBUGMODE
	outFile.open("C:\\HookLog.txt", ios::app);
#endif

	PDWORD temp;

	D3DXFONT_DESC fDesc;

#ifdef DEBUGMODE
	outFile << "Assigning pDevice to gameDevice\n";
	outFile.close();
	outFile.open("C:\\HookLog.txt", ios::app);
#endif


	temp = (PDWORD)*pDevice;
	gameDevice = (LPDIRECT3DDEVICE9)temp;

#ifdef DEBUGMODE
	outFile << "Success\n";
	outFile.close();
	outFile.open("C:\\HookLog.txt", ios::app);
#endif

#ifdef DEBUGMODE
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
#endif


	gameDevice->GetViewport(&mViewport);

	fDesc.CharSet = DEFAULT_CHARSET;
	strcpy_s(fDesc.FaceName, -1, "Impact");
	fDesc.Height = 24;
	fDesc.Italic = false;
	fDesc.MipLevels = 1;
	fDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	fDesc.Quality = PROOF_QUALITY;
	fDesc.Weight = FW_NORMAL;
	fDesc.Width = NULL;

#ifdef DEBUGMODE
	outFile << "Creating Line and Font\n";
#endif


	D3DXCreateLine(gameDevice, &mLine);
	D3DXCreateFontIndirect(gameDevice, &fDesc, &mFont);

	generateShader();
	generateTexture();

#ifdef DEBUGMODE
	outFile << "Success\n";
	outFile.close();
#endif

}
void d3dManager::drawRectOutline(float x, float y, float length, float width, float thickness, D3DCOLOR color)
{
	LPD3DXVECTOR2 pVec2Top = new D3DXVECTOR2[2];
	LPD3DXVECTOR2 pVec2Right = new D3DXVECTOR2[2];
	LPD3DXVECTOR2 pVec2Bottom = new D3DXVECTOR2[2];
	LPD3DXVECTOR2 pVec2Left = new D3DXVECTOR2[2];

	pVec2Top[0].x = x;
	pVec2Top[0].y = y - (thickness / 2);
	pVec2Top[1].x = x + length;
	pVec2Top[1].y = y - (thickness / 2);

	pVec2Right[0].x = x + length;
	pVec2Right[0].y = y - (thickness / 2);
	pVec2Right[1].x = x + length;
	pVec2Right[1].y = y + width - (thickness / 2);

	pVec2Bottom[0].x = x + length;
	pVec2Bottom[0].y = y + width - (thickness / 2);
	pVec2Bottom[1].x = x;
	pVec2Bottom[1].y = y + width - (thickness / 2);

	pVec2Left[0].x = x;
	pVec2Left[0].y = y + width - (thickness / 2);
	pVec2Left[1].x = x;
	pVec2Left[1].y = y - (thickness / 2);


	mLine->Begin();
	for (int i = 0; i < thickness; i++)
	{
		mLine->Draw(pVec2Top, 2, color);
		pVec2Top[0].y++;
		pVec2Top[1].y++;

		mLine->Draw(pVec2Right, 2, color);
		pVec2Right[0].x--;
		pVec2Right[1].x--;

		mLine->Draw(pVec2Bottom, 2, color);
		pVec2Bottom[0].y--;
		pVec2Bottom[1].y--;

		mLine->Draw(pVec2Left, 2, color);
		pVec2Left[0].x++;
		pVec2Left[1].x++;
	}

	mLine->End();

	delete [] pVec2Top;
	delete [] pVec2Right;
	delete [] pVec2Bottom;
	delete [] pVec2Left;

	pVec2Top = NULL;
	pVec2Right = NULL;
	pVec2Bottom = NULL;
	pVec2Left = NULL;
}
void d3dManager::generateTexture()
{
	const BYTE byteRed[ 58 ] = {
		0x42, 0x4D, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
		0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00
	};

	const BYTE byteGreen[60] = 
	{
		0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
		0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x20, 0xA0, 0x00, 0x00, 0xFF, 0xFF
	};

	const BYTE byteBlue[60] = //Blue
	{
		0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
		0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	const BYTE byteOrange[60] = //orange
	{
		0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
		0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x10, 0x80, 0xF0, 0xB0, 0x00, 0x00
	};

	const BYTE byteYellow[60] = //yellow
	{
		0x42, 0x4D, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
		0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00
	};

	D3DXCreateTextureFromFileInMemory(gameDevice, byteRed, sizeof(byteRed), &pTexRed);
	D3DXCreateTextureFromFileInMemory(gameDevice, byteGreen, sizeof(byteGreen), &pTexGreen);
	D3DXCreateTextureFromFileInMemory(gameDevice, byteBlue, sizeof(byteBlue), &pTexBlue);
	D3DXCreateTextureFromFileInMemory(gameDevice, byteYellow, sizeof(byteYellow), &pTexYellow);
}
void d3dManager::generateShader()
{
	char szShader[256];
	LPD3DXBUFFER pShaderBuff = NULL;

	sprintf(szShader, "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", 0.0f, 1.0f, 0.0f, 1.0f);
	D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, NULL, &pShaderBuff, NULL);
	gameDevice->CreatePixelShader((const DWORD *)pShaderBuff->GetBufferPointer(), &shadeGreen);

	sprintf(szShader, "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", 0.0f, 0.0f, 1.0f, 1.0f);
	D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, NULL, &pShaderBuff, NULL);
	gameDevice->CreatePixelShader((const DWORD *)pShaderBuff->GetBufferPointer(), &shadeBlue);

	sprintf(szShader, "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", 1.0f, 1.0f, 0.0f, 1.0f);
	D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, NULL, &pShaderBuff, NULL);
	gameDevice->CreatePixelShader((const DWORD *)pShaderBuff->GetBufferPointer(), &shadeYellow);

	sprintf(szShader, "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", 1.0f, 0.0f, 0.0f, 1.0f);
	D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, NULL, &pShaderBuff, NULL);
	gameDevice->CreatePixelShader((const DWORD *)pShaderBuff->GetBufferPointer(), &shadeRed);

	ReleaseCom(pShaderBuff);
}
void d3dManager::drawShadedRect(float x, float y, float length, float width, D3DCOLOR color)
{
	LPD3DXVECTOR2 vec = new D3DXVECTOR2[2];

	vec[0].x = x;
	vec[0].y = y;
	vec[1].x = x + length;
	vec[1].y = y;

	mLine->Begin();

	for (int i = NULL; i < (int)width; i++)
	{
		mLine->Draw(vec, 2, color);

		vec[0].y++;
		vec[1].y++;
	}

	delete [] vec;
	vec = NULL;
}
void d3dManager::drawXhair(D3DCOLOR color)
{
	LPD3DXVECTOR2 vec1 = new D3DXVECTOR2[2];
	LPD3DXVECTOR2 vec2 = new D3DXVECTOR2[2];

	vec1[0].x = (float)mViewport.Width / 2 - 10;
	vec1[0].y = (float)mViewport.Height / 2;
	vec1[1].x = (float)mViewport.Width / 2 + 10;
	vec1[1].y = (float)mViewport.Height / 2;

	vec2[0].x = (float)mViewport.Width / 2;
	vec2[0].y = (float)mViewport.Height / 2 - 10;
	vec2[1].x = (float)mViewport.Width / 2;
	vec2[1].y = (float)mViewport.Height / 2 + 10;

	mLine->Begin();
	mLine->Draw(vec1, 2, color);
	mLine->Draw(vec2, 2, color);
	mLine->End();

	delete []vec1;
	delete []vec2;

	vec1 = NULL;
	vec2 = NULL;
}
void d3dManager::drawString(LPCSTR text, float x, float y, float length, float width, D3DCOLOR color, bool calcRect)
{
	LPRECT rect = new RECT;

	rect->left = (long)x;
	rect->top = (long)y;
	rect->right = (long)(x + length);
	rect->bottom = (long)(y + width);

	if (calcRect)
	{
		mFont->DrawTextA(NULL, text, -1, rect, DT_CALCRECT, color);
	}

	mFont->DrawTextA(NULL, text, -1, rect, DT_CENTER | DT_VCENTER | DT_NOCLIP, color);

	delete rect;
	rect = NULL;
}
float d3dManager::getClientWidth()
{
	return (float)mViewport.Width;
}
float d3dManager::getClientHeight()
{
	return (float)mViewport.Height;
}
void d3dManager::prereset()
{
	mFont->OnLostDevice();
	mLine->OnLostDevice();
}
void d3dManager::postreset()
{
	mFont->OnResetDevice();
	mLine->OnResetDevice();

	generateShader();
	generateTexture();
}
LPDIRECT3DTEXTURE9 d3dManager::getTexture(char *color)
{
	if (stricmp(color, "red") == NULL)
	{
		return pTexRed;
	}
	if (stricmp(color, "green") == NULL)
	{
		return pTexGreen;
	}
	if (stricmp(color, "blue") == NULL)
	{
		return pTexBlue;
	}
	if (stricmp(color, "yellow") == NULL)
	{
		return pTexYellow;
	}
}

LPDIRECT3DPIXELSHADER9 d3dManager::getShader(char *color)
{
	if (stricmp(color, "red") == NULL)
	{
		return shadeRed;
	}
	if (stricmp(color, "green") == NULL)
	{
		return shadeGreen;
	}
	if (stricmp(color, "blue") == NULL)
	{
		return shadeBlue;
	}
	if (stricmp(color, "yellow") == NULL)
	{
		return shadeYellow;
	}
}