#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

SlPlayer slPlayers[SL_PLAYER_COUNT];
int totalPlayerCount = 0;

void slAddPlayer(SlPlayer player) {
   
    if(totalPlayerCount <= SL_PLAYER_COUNT) {
     int index = totalPlayerCount;
     strcpy(slPlayers[index].name, player.name);
     slPlayers[index].playerIsInBoard = player.playerIsInBoard;
     slPlayers[index].position = player.position;
     totalPlayerCount++;
    }
}

SlPlayer * slGetPlayers(int k) {
    return slPlayers + k;
}

int * slGetPlayerCount() {
    return &totalPlayerCount;
}
void slDebugPlayers(SlPlayer players[SL_PLAYER_COUNT]) {
    for (int i=0; i < totalPlayerCount; i++) {
        printf("Player Name: %s\n", slPlayers[i].name);
    }
}