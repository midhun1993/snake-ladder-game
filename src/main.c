#include <stdio.h>
#include "board.h"
#include "player.h"
#include "gui.h"

int main(int argc, char** argv) {
	slBoardInstance;
	slPlayers;
	slBootstrapBoard(slBoardInstance); 
	// slDebugBoard(slBoardInstance);
	SlPlayer player = {
		"Midhun",
		2,
		true
	};
	slAddPlayer(player);
	//slDebugPlayers(slPlayers);
	slGameWindowInit(&argc, argv);
}
