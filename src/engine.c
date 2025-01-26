#include "player.h"
#include "board.h"
#include<GL/glut.h> 
#include<GL/freeglut.h>

void slRunBoardComputation( SlCell *board, SlPlayer *p1, int dice) {
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

void slKeyboard(unsigned char key,
              int x, int y)
{
    slDiceValue = slRollTheDice();
    int *totalPlayer = slGetPlayerCount();
    int *currentPlayer = slGetCurrentPlayer();
    if(0 == *currentPlayer) {
        *currentPlayer = 0;
    } 
    if(*currentPlayer >= *totalPlayer) {
        *currentPlayer = 0;
    }

    SlPlayer * player = slGetPlayers(*currentPlayer);
	slRunBoardComputation(slBoardInstance, player, slDiceValue);
	glutPostRedisplay();
    *currentPlayer = *currentPlayer + 1;
}