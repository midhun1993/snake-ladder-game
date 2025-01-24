#ifndef BOARD_H  
#define BOARD_H
#include <stdbool.h>  

#define SL_SNAKE_COUNT 8
#define SL_LADDER_COUNT 9
#define SL_CELL_COUNT 100

typedef struct  
{
    int pos;
	int deltaValue;
	bool isSnakeMouth;
	bool isLadderEntry;  
} SlCell;



extern  SlCell slBoardInstance[SL_CELL_COUNT];
extern int slDiceValue;

void slBootstrapBoard(SlCell *boardInstace);
int slRollTheDice(void);
void slDebugBoard(SlCell *boardInstace);
SlCell slFindCell(int i);
#endif 