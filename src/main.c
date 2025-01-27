#include <stdio.h>
#include "board.h"
#include "player.h"
#include "gui.h"

int main(int argc, char** argv) {
	slBoardInstance;
	slPlayers;
	slBootstrapBoard(slBoardInstance); 
	// slDebugBoard(slBoardInstance);
	SlPlayer player1 = {
		"Player 1",
		1,
		false,
		{255.0f, 75.0f, 0.0f}
	};

	SlPlayer player2 = {
		"Player 2",
		1,
		false,
		{255.0f, 0.0f, 0.0f}
	};
	slAddPlayer(player1);
	slAddPlayer(player2);
	slDebugPlayers(slPlayers);
	slGameWindowInit(&argc, argv); 
}
