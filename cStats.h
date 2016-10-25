#ifndef CSTATS_H
#define CSTATS_H
#define WIN32_LEAN_AND_MEAN


class cStats
{
public:
	__int32 Current_Exp; //0000
	__int32 Current_Score; //0004
	__int32 Kills; //0008
	__int32 Best_Streak; //000C
	__int32 Deaths; //0010
	char unknown0[4];
	__int32 Assists; //0018
	__int32 HeadShots; //001C
	char unknown1[8];
	__int32 Time_Ingame; //0028
	char unknown2[8];
	__int32 Time_Ingame_2; //0034 - given in seconds
	char unknown3[8];
	__int32 Games_Played; //0040
	char unknown4[16];
	__int32 Total_Hits; //0054
	__int32 Missed_shots; //0058
	__int32 Total_Shots_2; //005C
	char unknown5[100];
	__int32 Level; //00C4
	__int32 Pointtotal_at_last_level_up; //00C8
	__int32 PointTotal_for_next_levelup; //00CC
	__int32 PointTotal_at_start_of_map; //00D0
};

extern bool statsSet;
extern cStats *stats;
extern cStats statsAtStart;

void setStartingStats();

#endif