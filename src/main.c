#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ncurses.h>
#include<GL/glut.h> 
#include<math.h> 

#define GL_COLUMNS_SIZE 100
#define GL_SNAKE_COUNT 8
#define GL_LADDER_COUNT 9

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
	bool playerIsInBoard;
};

struct SnakePosition snakePos[GL_SNAKE_COUNT] = {
	{47, 47 - 26},
	{49, 49 - 11},
	{58, 58 - 41},
	{61, 61 - 19},
	{86, 86 - 24},
	{93, 93 - 72},
	{95, 95 - 75 },
	{98, 98 - 79}
};

struct LadderPosition ladderPos[GL_LADDER_COUNT] = {
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

struct Column board[GL_COLUMNS_SIZE];

void slBootstrapBoard(struct Column *board) {
	for(int i =0; i < GL_COLUMNS_SIZE; i++ ){
		board[i].pos = i+1;
		board[i].deltaValue = 0;
		board[i].isLadderEntry = false;
		board[i].isSnakeMouth = false;
		
	}

	// assign snake pos
	for(int j = 0; j < GL_SNAKE_COUNT; j++) {
		int snakeMouthPos = snakePos[j].snakeMouth;
		int columnPositionInBoard = snakeMouthPos - 1;
		board[columnPositionInBoard].isSnakeMouth = true;
		board[columnPositionInBoard].deltaValue  = snakePos[j].subValue;
	}

	// assign ladder pos
	for(int h = 0; h < GL_LADDER_COUNT; h++) {
		int ladderEntryPos = ladderPos[h].ladderEntry;
		int columnPositionInBoard = ladderEntryPos - 1;
		board[columnPositionInBoard].isLadderEntry = true;
		board[columnPositionInBoard].deltaValue  = ladderPos[h].addValue;
	}
}

void slDebugBoard( struct Column *board) {
	for(int i =0; i< GL_COLUMNS_SIZE; i++) {
		printf("----------------------------------------\n");
		printf("Board Pos: %d \n", board[i].pos);
		printf("isLadderEntry: %d \n", board[i].isLadderEntry);
		printf("isSnakeMouth: %d \n", board[i].isSnakeMouth);
		printf("deltaValue: %d \n", board[i].deltaValue );
	}
}

int slRollTheDice() {
	const int MAX = 6;
	const int MIN = 1;
	int val = rand()%(MAX - MIN + 1) + MIN;	
	return val;
}

void slRunBoardComputation( struct Column *board, struct Player *p1, int dice) {
	if(p1->playerIsInBoard) {
		int pos = p1->position;
		int targetPos = pos + dice;
		if(board[targetPos - 1].isLadderEntry == true) {
			targetPos += board[targetPos - 1].deltaValue;
		}

		if(board[targetPos - 1].isSnakeMouth == true) {
			targetPos -= board[targetPos - 1].deltaValue;
		}
		p1->position = targetPos;

	} else {
		if(dice == 1) {
			p1->playerIsInBoard = true;
			p1->position = 1;
		}
	}
}

void slShowPlayerStat(struct Column *board, struct Player *p1, int dice) {
	printf("dice landed on %d and you are at:%d \n", dice, p1->position);
}

void slStartGame( struct Column *board, struct Player *p1) {
	while(true){
		initscr();
		cbreak();
		printf("Press any key when you are ready!\n");
		char c = getch();
		endwin();
		int diceValue = slRollTheDice();
		slRunBoardComputation(board, p1, diceValue);
		slShowPlayerStat(board, p1, diceValue);
	}

}
void slDrawBoard(void) {
	glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POINTS); 
    float x, y, z, w; 
	 
	// for ( i = 0; i <GL_COLUMNS_SIZE; i++ ) 
    // { 
	// 	/** Todo will write the logic soon */
	// 	glVertex2i(x, y); 
    // } 
    glEnd(); 
    glFlush(); 	
}

// function to initialize 
void slInitWindowConfig (void) 
{ 
    glClearColor(255.0, 255.0, 255.0, 1.0); 
      
    // making picture color green (in RGB mode), as middle argument is 1.0 
    glColor3f(0.0, 0.0, 0.0); 
      
    // breadth of picture boundary is 1 pixel 
    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
      
    // No idea what it's 
    gluOrtho2D(-780, 780, -420, 420); 
} 

int main(int argc, char** argv) {
	
	struct Player p1 = {
		0, false
	};
	// Board init
	slBootstrapBoard(board);
	//slDebugBoard(board);
	//slStartGame(board, &p1);	

	glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(1366, 768); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Snake and Ladder"); 
	slInitWindowConfig();
	glutDisplayFunc(slDrawBoard);
	

	glutMainLoop(); 


}
