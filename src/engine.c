

// void slRunBoardComputation( struct Column *board, struct Player *p1, int dice) {
// 	if(p1->playerIsInBoard) {
// 		int pos = p1->position;
// 		int targetPos = pos + dice;
// 		if(board[targetPos - 1].isLadderEntry == true) {
// 			targetPos += board[targetPos - 1].deltaValue;
// 		}

// 		if(board[targetPos - 1].isSnakeMouth == true) {
// 			targetPos -= board[targetPos - 1].deltaValue;
// 		}
// 		p1->position = targetPos;

// 	} else {
// 		if(dice == 1) {
// 			p1->playerIsInBoard = true;
// 			p1->position = 1;
// 		}
// 	}
// }