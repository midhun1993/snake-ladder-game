#ifndef PLAYER_H  
#define PLAYER_H

#define SL_PLAYER_COUNT 6

#include<stdbool.h>


typedef struct 
{
    char name[50];
    int position;
	bool playerIsInBoard;
   
} SlPlayer;

extern SlPlayer slPlayers[SL_PLAYER_COUNT];
void slAddPlayer(SlPlayer player);
void slDebugPlayers(SlPlayer slAddPlayers[SL_PLAYER_COUNT]);
#endif 