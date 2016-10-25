#include "cStats.h"
#include <Windows.h>

cStats *stats = (cStats *)0x0CC19918;
cStats statsAtStart;
bool statsSet = false;

void setStartingStats()
{
	statsAtStart.Assists = stats->Assists;
	statsAtStart.Best_Streak = stats->Best_Streak;
	statsAtStart.Current_Exp = stats->Current_Exp;
	statsAtStart.Current_Score = stats->Current_Score;
	statsAtStart.Deaths = stats->Deaths;
	statsAtStart.Games_Played = stats->Games_Played;
	statsAtStart.HeadShots = stats->HeadShots;
	stats->Kills = stats->Kills;
	statsAtStart.Level = stats->Level;
	statsAtStart.Missed_shots = stats->Missed_shots;
	statsAtStart.Pointtotal_at_last_level_up = stats->Pointtotal_at_last_level_up;
	statsAtStart.PointTotal_at_start_of_map = stats->PointTotal_at_start_of_map;
	statsAtStart.PointTotal_for_next_levelup = stats->PointTotal_for_next_levelup;
	statsAtStart.Time_Ingame = stats->Time_Ingame;
	statsAtStart.Time_Ingame_2 = stats->Time_Ingame_2;
	statsAtStart.Total_Hits = stats->Total_Hits;
	statsAtStart.Total_Shots_2 = stats->Total_Shots_2;
}