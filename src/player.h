#ifndef PLAYER_H  
#define PLAYER_H

#include<stdbool.h>

#define SL_PLAYER_COUNT 6




typedef struct 
{
    char name[50];
    int position;
	bool playerIsInBoard;
    float colorVec[3];
   
} SlPlayer;

extern SlPlayer slPlayers[SL_PLAYER_COUNT];
void slAddPlayer(SlPlayer player);
void slDebugPlayers(SlPlayer slAddPlayers[SL_PLAYER_COUNT]);
SlPlayer * slGetPlayers(int k);
int * slGetPlayerCount(void);
int * slGetCurrentPlayer(void);
#endif 