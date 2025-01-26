#include<GL/glut.h> 
#include<math.h> 
#include<GL/freeglut.h>
#include "board.h"
#include "gui.h"
#include "player.h"
#include "engine.h"
#include<stdio.h>

#define SL_MAX_WIDTH_OF_CANVAS  1560
#define SL_MAX_HEIGHT_OF_CANVAS  840

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius,  SlPlayer * player) {
    int numSegments = 100; // Number of segments for smoothness
    GLfloat angle;
    printf("color %f, %f, %f",player->colorVec[0],player->colorVec[1],player->colorVec[2]);
    glColor3f(player->colorVec[0],player->colorVec[1],player->colorVec[2]); 
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle

    for (int i = 0; i <= numSegments; i++) {
        angle = i * 2.0f * 3.1415926f / numSegments; // Calculate the angle
        GLfloat dx = radius * cosf(angle);          // X coordinate
        GLfloat dy = radius * sinf(angle);          // Y coordinate
        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}

void slPlayersCards() {
    int *totalPlayerCount = slGetPlayerCount();
    int startWidth = SL_CELL_COUNT * 10  + 10;
     for(int k=0; k < *totalPlayerCount; k++) {
        SlPlayer * player =  slGetPlayers(k);
        glRasterPos3f(startWidth,  15, 1);
        glutBitmapString(GLUT_BITMAP_8_BY_13, player->name);
        startWidth += 150;
     }

}


void slDrawCell(SlPoint p1, SlPoint p2, SlPoint p3, SlPoint p4, SlCell cell){
    int *totalPlayerCount = slGetPlayerCount();
    char colstr[5];
	sprintf(colstr, "%d", cell.pos);
    
	glRasterPos3f(p3.x - 20, p3.y - 10, 1);
	glutBitmapString(GLUT_BITMAP_8_BY_13, colstr);
    for(int k=0; k < *totalPlayerCount; k++) {
        SlPlayer * player =  slGetPlayers(k);
        if(player->playerIsInBoard && player->position == cell.pos) {
            GLfloat x = p1.x + GL_CELL_WIDTH_AND_HEIGHT/2;
            GLfloat y = p1.y + GL_CELL_WIDTH_AND_HEIGHT/2;
            drawFilledCircle(x, y, 10, player);     
        }

       if(cell.isSnakeMouth) {
            glRasterPos3f(p1.x + 5,  p1.y + 5, 1);
            glutBitmapString(GLUT_BITMAP_8_BY_13, "Snake Mouth");
	    }

        if(cell.isLadderEntry) {
            glRasterPos3f(p1.x + 5, p1.y + 10, 1);
            glutBitmapString(GLUT_BITMAP_8_BY_13, "Ladder Start");
	    }
    }

	
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2i(p1.x, p1.y);
        glVertex2i(p2.x, p2.y);
        glVertex2i(p3.x, p3.y);
        glVertex2i(p4.x, p4.y);
    glEnd();
}

void slDrawBoard(void) {
	// We are planing to draw equal size SlCell 	
	const int START_X  = 10;
	const int START_Y = 10;

	glClear(GL_COLOR_BUFFER_BIT); 
	glLineWidth(30);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	char colstr[5];
	sprintf(colstr, "%d",slDiceValue);
	glRasterPos3f(1560 - 20, 10, 1);
	glutBitmapString(GLUT_BITMAP_8_BY_13, colstr);

    slPlayersCards();
	
	int startX = START_X;
	int startY = START_Y;

	for(int i =0; i < SL_CELL_COUNT; i++) {
		SlPoint p1, p2, p3, p4;	    
		p1.x = startX;
		p1.y = startY;

		p2.x = startX + GL_CELL_WIDTH_AND_HEIGHT;
		p2.y = startY;

		p3.x = startX + GL_CELL_WIDTH_AND_HEIGHT;
		p3.y = startY + GL_CELL_WIDTH_AND_HEIGHT;

		p4.x = startX;
		p4.y = startY + GL_CELL_WIDTH_AND_HEIGHT;
		SlCell cell = slFindCell(i);
		slDrawCell(p1, p2, p3, p4, cell);
	
		startX += GL_CELL_WIDTH_AND_HEIGHT;
		if((i+1)%10 == 0) {
			startX = START_X;
			startY = startY + GL_CELL_WIDTH_AND_HEIGHT;
		}
	}
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    gluOrtho2D(0, SL_MAX_WIDTH_OF_CANVAS, SL_MAX_HEIGHT_OF_CANVAS, 0); 
} 





void slGameWindowInit(int * argc, char ** argv) {
   
	glutInit(argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(1366, 768); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Snake and Ladder"); 
	slInitWindowConfig();
	glutDisplayFunc(slDrawBoard);
	
	 // Keyboard event handler
    glutKeyboardFunc(slKeyboard);
	glutMainLoop();
	glFinish();
}