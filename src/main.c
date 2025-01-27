#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ncurses.h>
#include<GL/glut.h> 
#include<math.h> 
#include <GL/freeglut.h>

#define GL_COLUMNS_SIZE 100
#define GL_SNAKE_COUNT 8
#define GL_LADDER_COUNT 9
#define GL_CELL_WIDTH_AND_HEIGHT 80

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

struct Point {
	int x;
	int y;
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

struct Player player1 = {
		0, false
};

int diceValue = 0;

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
		diceValue = slRollTheDice();
		slRunBoardComputation(board, p1, diceValue);
		slShowPlayerStat(board, p1, diceValue);
	}

}

void slDrawCell(struct Point p1, struct Point p2, struct Point p3, struct Point p4, struct Column cell){

	char colstr[5];
	sprintf(colstr, "%d", cell.pos);
	
	glRasterPos3f(p3.x - 20, p3.y - 10, 1);
	glutBitmapString(GLUT_BITMAP_8_BY_13, colstr);

	if(player1.playerIsInBoard && player1.position == cell.pos) {
		glRasterPos3f(p1.x + 20, p1.y + 10, 1);
		glutBitmapString(GLUT_BITMAP_8_BY_13, "You");
	}

    glBegin(GL_POLYGON);
        glVertex2i(p1.x, p1.y);
        glVertex2i(p2.x, p2.y);
        glVertex2i(p3.x, p3.y);
        glVertex2i(p4.x, p4.y);
    glEnd();
}

struct Column slFindCell(int i) {
	int flag = (int)((int)round(i/10)%2);
	if(flag == 0) {
		// normal
		int indx = GL_COLUMNS_SIZE - (i+1);
		return board[indx];
	} else {
		// reverse
		int r = (int)round(i  / 10) + 1;
		int mod = (int) i % 10; 
		int indx = GL_COLUMNS_SIZE - (r * 10) + mod ;
		return board[indx];
	}

}


void slDrawBoard(void) {
	// We are planing to draw equal size column 	
	const int START_X  = 10;
	const int START_Y = 10;

	glClear(GL_COLOR_BUFFER_BIT); 
	glLineWidth(30);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	char colstr[5];
	sprintf(colstr, "%d",diceValue);
	glRasterPos3f(1560 - 20, 10, 1);
	glutBitmapString(GLUT_BITMAP_8_BY_13, colstr);
	
	int startX = START_X;
	int startY = START_Y;

	for(int i =0; i < GL_COLUMNS_SIZE; i++) {
		struct Point p1, p2, p3, p4;	    
		p1.x = startX;
		p1.y = startY;

		p2.x = startX + GL_CELL_WIDTH_AND_HEIGHT;
		p2.y = startY;

		p3.x = startX + GL_CELL_WIDTH_AND_HEIGHT;
		p3.y = startY + GL_CELL_WIDTH_AND_HEIGHT;

		p4.x = startX;
		p4.y = startY + GL_CELL_WIDTH_AND_HEIGHT;
		struct Column cell = slFindCell(i);
		slDrawCell(p1, p2, p3, p4, cell);
	
		startX += GL_CELL_WIDTH_AND_HEIGHT;
		if((i+1)%10 == 0) {
			startX = START_X;
			startY = startY + GL_CELL_WIDTH_AND_HEIGHT;
		}
	}
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
      
    // This is the base of co-ordinate system 
    gluOrtho2D(0, 1560, 840, 0); 
} 

void slMouseClick() {
	//printf("esss");
}

void slKeyboard(unsigned char key,
              int x, int y)
{
	diceValue = slRollTheDice();
	slRunBoardComputation(board, &player1, diceValue);
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	
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
	glutMouseFunc(slMouseClick);

	 // Keyboard event handler
    glutKeyboardFunc(slKeyboard);
	glutMainLoop();
	glFinish();
}
