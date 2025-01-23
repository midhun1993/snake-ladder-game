#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ncurses.h>
#define COLUMNS_SIZE 100
#define SNAKE_COUNT 8
#define LADDER_COUNT 9

struct Column  {
	int pos;
	int deltaValue;
	bool isSnakeMouth;
	bool isLadderEntry; 
};


struct SnakePosition {
	int snakeMouth;
	int subValue;
};

struct LadderPosition {
	int ladderEntry;
	int addValue;
};

struct Player {
	int position;
};

struct SnakePosition snakePos[SNAKE_COUNT] = {
	{47, 47 - 26},
	{49, 49 - 11},
	{58, 58 - 41},
	{61, 61 - 19},
	{86, 86 - 24},
	{93, 93 - 72},
	{95, 95 - 75 },
	{98, 98 - 79}
};

struct LadderPosition ladderPos[LADDER_COUNT] = {
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

void bootstrap_board(struct Column *board) {
	for(int i =0; i < COLUMNS_SIZE; i++ ){
		board[i].pos = i+1;
	}

	// assign snake pos
	for(int j = 0; j < SNAKE_COUNT; j++) {
		int snakeMouthPos = snakePos[j].snakeMouth;
		int columnPositionInBoard = snakeMouthPos - 1;
		board[columnPositionInBoard].isSnakeMouth = true;
		board[columnPositionInBoard].deltaValue  = snakePos[j].subValue;
	}

	// assign ladder pos
	for(int h = 0; h < LADDER_COUNT; h++) {
		int ladderEntryPos = ladderPos[h].ladderEntry;
		int columnPositionInBoard = ladderEntryPos - 1;
		board[columnPositionInBoard].isLadderEntry = true;
		board[columnPositionInBoard].deltaValue  = ladderPos[h].addValue;
	}
}

void debug_board( struct Column *board) {
	for(int i =0; i< COLUMNS_SIZE; i++) {
		printf("----------------------------------------\n");
		printf("Board Pos: %d \n", board[i].pos);
		printf("isLadderEntry: %d \n", board[i].isLadderEntry);
		printf("isSnakeMouth: %d \n", board[i].isSnakeMouth);
		printf("deltaValue: %d \n", board[i].deltaValue );
	}
}

int roll_the_dice() {
	const int MAX = 6;
	const int MIN = 1;
	int val = rand()%(MAX - MIN + 1) + MIN;	
	return val;
}

void start_game( struct Column *board, struct Player p1) {
	
	while(true){
		initscr();
		cbreak();
        noecho();
		printf("Press any key when you are ready!\n");
		char c = getch();
		endwin();
		printf("Dice value: %d \n", roll_the_dice());
	}

}

int main() {
	struct Column board[COLUMNS_SIZE];
	struct Player p1;
	bootstrap_board(board);
	//debug_board(board);
	start_game(board, p1);	
}
