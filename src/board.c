#include<stdbool.h>
#include<math.h>
#include "board.h"
#include<math.h>
#include<stdio.h>
#include <stdlib.h>

struct  SlSnakePosition
{
   int snakeMouthPos;
   int subValue;
};

struct SlLadderPosition {
	int ladderEntryPos;
	int addValue;
};


struct SlSnakePosition snakePositions[SL_SNAKE_COUNT] = {
	{47, 47 - 26},
	{49, 49 - 11},
	{58, 58 - 41},
	{61, 61 - 19},
	{86, 86 - 24},
	{93, 93 - 72},
	{95, 95 - 75 },
	{98, 98 - 79}
};

struct SlLadderPosition ladderPostions[SL_LADDER_COUNT] = {
	{4, 14 - 4 },
	{9, 31 - 9},
	{20, 37 - 20},
	{21, 42 - 21},
	{28, 84 - 28},
	{36, 57 - 36},
	{51, 73 - 51},
	{71, 92 - 71},
	{80, 99 - 80}
};

/** */

SlCell slBoardInstance[SL_CELL_COUNT];
int slDiceValue = 0;

void slBootstrapBoard(SlCell *board) {
    for(int i =0; i < SL_CELL_COUNT; i++ ){
		board[i].pos = i+1;
		board[i].deltaValue = 0;
		board[i].isLadderEntry = false;
		board[i].isSnakeMouth = false;
		
	}

	// assign snake pos
	for(int j = 0; j < SL_SNAKE_COUNT; j++) {
		int snakeMouthPos = snakePositions[j].snakeMouthPos;
		int columnPositionInBoard = snakeMouthPos - 1;
		board[columnPositionInBoard].isSnakeMouth = true;
		board[columnPositionInBoard].deltaValue  = snakePositions[j].subValue;
	}

	// assign ladder pos
	for(int h = 0; h < SL_LADDER_COUNT; h++) {
		int ladderEntryPos = ladderPostions[h].ladderEntryPos;
		int columnPositionInBoard = ladderEntryPos - 1;
		board[columnPositionInBoard].isLadderEntry = true;
		board[columnPositionInBoard].deltaValue  = ladderPostions[h].addValue;
	}
}

int slRollTheDice() {
	const int MAX = 6;
	const int MIN = 1;
	int val = rand()%(MAX - MIN + 1) + MIN;	
	return val;
}

void slDebugBoard(SlCell *board) {
	for(int i =0; i< SL_CELL_COUNT; i++) {
		printf("----------------------------------------\n");
		printf("Board Pos: %d \n", board[i].pos);
		printf("isLadderEntry: %d \n", board[i].isLadderEntry);
		printf("isSnakeMouth: %d \n", board[i].isSnakeMouth);
		printf("deltaValue: %d \n", board[i].deltaValue );
	}
}

 SlCell slFindCell(int i) {
	int flag = (int)((int)round(i/10)%2);
	if(flag == 0) {
		// normal
		int indx = SL_CELL_COUNT - (i+1);
		return slBoardInstance[indx];
	} else {
		// reverse
		int r = (int)round(i  / 10) + 1;
		int mod = (int) i % 10; 
		int indx = SL_CELL_COUNT - (r * 10) + mod ;
		return slBoardInstance[indx];
	}
}



