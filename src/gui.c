#include<GL/glut.h> 
#include<math.h> 
#include <GL/freeglut.h>



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