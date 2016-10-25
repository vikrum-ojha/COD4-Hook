#ifndef CMENU
#define CMENU
#define WIN32_LEAN_AND_MEAN


#include "d3dManager_Hack.h"
#include "cHacks.h"

enum AimbotCvars	{aAimbot = 0, aFOV = 1, aSmoothAim = 2, aAimCheck = 3};
enum EspCvars		{eNametags = 0, eDistance = 1, eBoundingBoxes = 2, eClass = 3, eGrenade = 4};
enum VisualsCvars	{vCrosshair = 0, vLaser = 1, vChams = 2,  vAsusWalls = 3};
enum RemovableCvars {rRecoil = 0, rFog = 1, rSmoke = 2, rFlash = 3, rRain = 4, rSniperScope = 5};
enum OthersCvars	{oOthers = 0, oRenderMode = 1};

struct cMenu
{
	static const int CategoryAmount		= 5;
	static const int AimbotAmount		= 4;
	static const int EspAmount			= 5;
	static const int VisualsAmount		= 4;
	static const int RemovablesAmount	= 6;
	static const int OthersAmount		= 2;

	struct cVars
	{
		char name[32];
		int status;
		int optionCap;
	};

	bool draw;
	bool init;

	float cellWidth;
	float cellHeight;
	float edgeSpacing;
	
	int catNum;
	int vertCount;
	int maxVertCount;

	cVars categories[CategoryAmount];
	cVars aimbot[AimbotAmount];
	cVars esp[EspAmount];
	cVars visuals[VisualsAmount];
	cVars removables[RemovablesAmount];
	cVars other[OthersAmount];

	cHacks hObject;

	cMenu(): draw(false), init(false), catNum(NULL), vertCount(-1), maxVertCount(-1)
	{
		char *cats[] = {"Aimbot", "ESP", "Visuals", "Removables", "Other"};
		char *catsAimbot[] = {"Aimbot", "FOV", "Smooth Aim", "Aim Check"};
		char *catsEsp[] = {"Nametags", "Distance", "Bounding Boxes", "Class", "Grenade"};
		char *catsVisuals[] = {"Crosshair", "Laser", "Chams", "Asus Walls"};
		char *catsRemovables[] = {"No Recoil", "No Fog", "No Smoke", "No Flash", "No Rain", "No Sniper Scope"};
		char *catsOther[] = {"Rapidfire", "Render Mode"};

		categories[0].optionCap = AimbotAmount;
		categories[1].optionCap = EspAmount;
		categories[2].optionCap = VisualsAmount;
		categories[3].optionCap = RemovablesAmount;
		categories[4].optionCap = OthersAmount;

		char **insert = cats;

		for (int i = NULL; i < CategoryAmount; i++)
		{
			categories[i].status = -1;
			strcpy_s(categories[i].name, -1, *insert);

			insert++;
		}

		insert = catsAimbot;

		for (int i = NULL; i < AimbotAmount; i++)
		{
			aimbot[i].status = -1;
			if (i == 1)
			{
				aimbot[i].optionCap = 360;
				aimbot[i].status = 0;
			}
			else
			{
				aimbot[i].optionCap = 1;
			}
			
			aimbot[i].status = -1;
			strcpy_s(aimbot[i].name, -1, *insert);

			insert++;
		}

		insert = catsEsp;

		for (int i = NULL; i < EspAmount; i++)
		{
			esp[i].status = -1;
			esp[i].optionCap = 1;
			esp[i].status = -1;
			strcpy_s(esp[i].name, -1, *insert);

			insert++;
		}

		insert = catsVisuals;

		for (int i = NULL; i < VisualsAmount; i++)
		{
			visuals[i].status = -1;
			visuals[i].optionCap = 1;
			visuals[i].status = -1;
			strcpy_s(visuals[i].name, -1, *insert);

			insert++;
		}

		visuals[vChams].optionCap = 2;

		insert = catsRemovables;

		for (int i = NULL; i < RemovablesAmount; i++)
		{
			removables[i].status = -1;
			removables[i].optionCap = 1;
			removables[i].status = -1;
			strcpy_s(removables[i].name, -1, *insert);

			insert++;
		}

		insert = catsOther;

		for (int i = NULL; i < OthersAmount; i++)
		{
			if (i == 1)
			{
				other[i].optionCap = 2;
				other[i].status = 0;
			}
			else
			{
				other[i].optionCap = 1;
				other[i].status = -1;
			}
			strcpy_s(other[i].name, -1, *insert);

			insert++;
		}
	}
	~cMenu()
	{}
	bool navigate()
	{
		maxVertCount = categories[catNum].optionCap;

		if (GetAsyncKeyState(VK_INSERT) &1)
		{
			draw = !draw;

			return NULL;
		}
		if (draw)
		{
		if(GetAsyncKeyState(VK_UP) &1)
		{
			vertCount++;

			if (vertCount == maxVertCount)
			{
				vertCount = maxVertCount - 1;
			}

			return NULL;
		}
		else if(GetAsyncKeyState(VK_DOWN) &1)
		{
			vertCount--;

			if (vertCount < -1)
			{
				vertCount = -1;
			}

			return NULL;
		}
		else if(GetAsyncKeyState(VK_LEFT) &1)
		{
			if (vertCount == -1)
			{
				catNum--;
				if (catNum == -1)
				{
					catNum = 4;
				}
				return NULL;
			}
			
			else
			{
				if (catNum == 0)
				{
					if (aimbot[vertCount].status != 0)
					{
						aimbot[vertCount].status--;
					}
					return NULL;
				}
				else if (catNum == 1)
				{
					if (esp[vertCount].status != 0)
					{
						esp[vertCount].status--;
					}
					return NULL;
				}
				else if (catNum == 2)
				{
					if (visuals[vertCount].status != 0)
					{
						visuals[vertCount].status--;
					}
					return NULL;
				}
				else if (catNum == 3)
				{
					if (removables[vertCount].status != 0)
					{
						removables[vertCount].status--;
					}
					return NULL;
				}
				else if (catNum == 4)
				{
					if (other[vertCount].status != 0)
					{
						other[vertCount].status--;
					}
					return NULL;
				}
			}
		}
		else if(GetAsyncKeyState(VK_RIGHT) &1)
		{
			if (vertCount == -1)
			{
				catNum++;
				if (catNum == 5)
				{
					catNum = 0;
				}
				return NULL;
			}
			else
			{
				if (catNum == 0)
				{
					if (aimbot[vertCount].status == aimbot[vertCount].optionCap)
					{
						return NULL;
					}
					else
					{
						aimbot[vertCount].status++;

						return NULL;
					}
				}
				else if (catNum == 1)
				{
					if (esp[vertCount].status == esp[vertCount].optionCap)
					{
						return NULL;
					}
					else
					{
						esp[vertCount].status++;

						return NULL;
					}
				}
				else if (catNum == 2)
				{
					if (visuals[vertCount].status == visuals[vertCount].optionCap)
					{
						return NULL;
					}
					else
					{
						visuals[vertCount].status++;

						return NULL;
					}
				}
				else if (catNum == 3)
				{
					if (removables[vertCount].status == removables[vertCount].optionCap)
					{
						return NULL;
					}
					else
					{
						removables[vertCount].status++;

						return NULL;
					}
				}
				else if (catNum == 4)
				{
					if (other[vertCount].status == other[vertCount].optionCap)
					{
						return NULL;
					}
					else
					{
						other[vertCount].status++;

						return NULL;
					}
				}
			}	
		}
		}
		return NULL;
	}
	void drawBaseRows(d3dManager &manager)
	{
		float temp = NULL;

		if (!init)
		{
			cellHeight = 25;
			edgeSpacing = (float)(((int)manager.getClientWidth() % CategoryAmount) / 2);
			cellWidth = manager.getClientWidth() / CategoryAmount;

			init = true;
		}

		temp = edgeSpacing;
		
		if (draw)
		{
			for(int i = NULL; i < CategoryAmount; i++)
			{
				manager.drawShadedRect(temp, manager.getClientHeight() - cellHeight, cellWidth, cellHeight, red);
				manager.drawRectOutline(temp, manager.getClientHeight() - cellHeight, cellWidth, cellHeight, 3, white);
		
				if ((vertCount == -1) && (catNum == i))
				{
					manager.drawString(categories[i].name, temp, manager.getClientHeight() - cellHeight, cellWidth, cellHeight, black, false);
				}
				else
				{
					manager.drawString(categories[i].name, temp, manager.getClientHeight() - cellHeight, cellWidth, cellHeight, white, false);
				}

				temp = temp + cellWidth;
			}
		}	
	}
	void drawMenuLeaflets(d3dManager &manager)
	{
		if (draw)
		{
			float temp1, temp2;

			temp1 = edgeSpacing;
			temp2 = (float)manager.getClientHeight();

			if(vertCount > -1)
			{
				for (int i = NULL; i < categories[catNum].optionCap; i++)
				{
					manager.drawShadedRect(temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, 25, red);
					manager.drawRectOutline(temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, 25, 3, white);

					if (vertCount == i)
					{
						if (catNum == 0)
						{
							manager.drawString(aimbot[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, black, false);
						}
						if (catNum == 1)
						{
							manager.drawString(esp[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, black, false);
						}
						if (catNum == 2)
						{
							manager.drawString(visuals[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, black, false);
						}
						if (catNum == 3)
						{
							manager.drawString(removables[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, black, false);
						}
						if (catNum == 4)
						{
							manager.drawString(other[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, black, false);
						}
					}
					else
					{
						if (catNum == 0)
						{
							manager.drawString(aimbot[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, white, false);
						}
						if (catNum == 1)
						{
							manager.drawString(esp[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, white, false);
						}
						if (catNum == 2)
						{
							manager.drawString(visuals[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, white, false);
						}
						if (catNum == 3)
						{
							manager.drawString(removables[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, white, false);
						}
						if (catNum == 4)
						{
							manager.drawString(other[i].name, temp1 + (cellWidth * catNum), temp2 - (50 + (25 * i)), cellWidth, cellHeight, white, false);
						}
					}
				}
			}
		}
	}
	void drawStatus(d3dManager &manager)
	{
		if(draw)
		{
			int tStat = -1;

			if (vertCount > -1)
			{
				if (catNum == NULL)
				{
					if (vertCount != 1)
					{
						tStat = aimbot[vertCount].status;
					}
				}
				else if (catNum == 1)
				{
					tStat = esp[vertCount].status;
				}
				else if (catNum == 2)
				{
					tStat = visuals[vertCount].status;
				}
				else if (catNum == 3)
				{
					tStat = removables[vertCount].status;
				}
				else if (catNum == 4)
				{
					if (vertCount != 1)
					{
						tStat = other[vertCount].status;
					}
				}

				if ((catNum == 0) && (vertCount == 1))
				{
					char *temp = new char[4];

					itoa(aimbot[1].status, temp, 10);

					if (aimbot[1].status > 0)
					{
						manager.drawShadedRect(edgeSpacing, (float)manager.getClientHeight() - 75, cellWidth, cellHeight, red);
						manager.drawRectOutline(edgeSpacing, (float)manager.getClientHeight() - 75, cellWidth, cellHeight, 3, white);
						manager.drawString(temp, edgeSpacing, (float)manager.getClientHeight() - 75, cellWidth, cellHeight, black, false);
					}

					delete []temp;
					temp = NULL;
				}
				if ((catNum == 2) && (vertCount == 2))
				{
					manager.drawShadedRect(edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, red);
					manager.drawRectOutline(edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, 3, white);
					if(visuals[vChams].status == -1)
					{
						manager.drawString("Chams", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
					}

					else if (visuals[vChams].status == 0)
					{
						manager.drawString("Off", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
					}
					else if (visuals[vChams].status == 1)
					{
						manager.drawString("Texture", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
					}
					else if (visuals[vChams].status == 2)
					{
						manager.drawString("Pixel Shader", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
					}
				}
				if ((catNum == 4) && (vertCount == 1))
				{
					manager.drawShadedRect(edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, red);
					manager.drawRectOutline(edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, 3, white);
					if (other[oRenderMode].status == 0)
					{
						manager.drawString("Solid", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
					}
					else if (other[oRenderMode].status == 1)
					{
						manager.drawString("Wireframe", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
					}
					else if (other[oRenderMode].status == 2)
					{
						manager.drawString("Point", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
					}
				}
				if (tStat == NULL)
				{
					manager.drawShadedRect(edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, red);
					manager.drawRectOutline(edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, 3, white);
					manager.drawString("Off", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
				}
				else if (tStat == 1)
				{
					if ((catNum != 2) || (vertCount != 2))
					{
						manager.drawShadedRect(edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, red);
						manager.drawRectOutline(edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, 3,white);
						manager.drawString("On", edgeSpacing + (cellWidth * catNum), (float)manager.getClientHeight() - (50 + (vertCount * 25)), cellWidth, cellHeight, black, false);
					}
				}
			}
		}
	}
	void setStatus() //Pass in hack object to make it look cleaner.
	{
		//Sets the individual boolean status for all hacks and equates them to what is seen inside the menus.  Hence the <Category>[element].status and hObject<Category>[element].status nodes.
		int tStat = NULL;

		tStat = aimbot[0].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.aimbot = tStat;

		tStat = aimbot[2].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.smoothAim = tStat;

		tStat = aimbot[3].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.aimCheck = tStat;

		tStat = esp[0].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.nametags = tStat;

		tStat = esp[1].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.distance = tStat;

		tStat = esp[2].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.bBoxes = tStat;

		tStat = esp[3].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.className = tStat;

		tStat = esp[4].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.grenade = tStat;

		tStat = visuals[0].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.xHair = tStat;

		tStat = visuals[1].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.laser = tStat;

		tStat = visuals[2].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.chams = tStat;

		tStat = visuals[3].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.statsbox = tStat;

		tStat = removables[0].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.recoil = tStat;

		tStat = removables[1].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.fog = tStat;

		tStat = removables[2].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.smoke = tStat;

		tStat = removables[3].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.flash = tStat;

		tStat = other[0].status;
		if (tStat < 0)
		{
			tStat = 0;
		}
		hObject.rapidFire = tStat;

	} //Consider re-working and passing in a hack object instead.  Make it look cleaner and remove some dependencies.
	void hackThread(d3dManager &manager) //pass in hObject, or reference cMenu inside hObject instead and set from there.  Menu should be independant.
	{
			hObject.nametagsOn();
			hObject.laserOn();
			hObject.noRecoil();
			hObject.noFog();
			hObject.noFlash();
	}
};

#endif