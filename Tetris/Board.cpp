#include "Board.h"
#define WIDTH 12
#define HEIGHT 18

int board[WIDTH][HEIGHT];
void Board::createBoard() {
	for (int i = 0; i <= WIDTH+1; i++) {
		for (int j = 0; j <= HEIGHT; j++) {
			if (i == 0 || j == WIDTH-1 || i == HEIGHT-1) {
				board[i][j] = 1;
			}
			else board[i][j] = 0;
		}
	}
}
void Board::displayBoard() {
	for (int i = 0; i < WIDTH + 4; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (board[i][j] == 1) {

			}
		}
	}
}
//bool Board::isGameOver() {
//	for (int i = 0; i < HEIGHT; i++) {
//		if (board[i] == '0') return true;
//	}
//	return false;
//}

void Board::drawPiece(int piece, int rotation, int px, int py) {
	for (int i1 = px, i2 = 0; i1 < px + 4; i1++, i2++)
	{
		for (int j1 = py, j2 = 0; j1 < py + 4; j1++, j2++)
		{
			// Store only the blocks of the piece that are not holes
			if (pPiece->GetBlockType(piece, rotation, j2, i2) != 0)
				board[i1][j1] = 1;
		}
	}
}

void Board::removeLine(int py) {
	for (int i = py; i > 0; i--) {
		for (int j = 0; j < HEIGHT; j++) {
			board[i][j] = board[i - 1][j];
		}
	}
}

bool Board::inside(int px, int py) {
	return (py > 0 && py < HEIGHT + 4 && px >= 0 && px < WIDTH);
}

int Board::left(int px, int py) {
	if (inside(px, py) && py > 0 && board[py][px - 1] == 0) return 1;
	else return 0;
}

int Board::right(int px, int py) {
	if (inside(px, py) && py > 0 && board[py][px + 1] == 0) return 1;
	else return 0;
}

int Board::down(int px, int py) {
	if (inside(px, py) && py > 0 && board[py+1][px] == 0) return 1;
	else return 0;
}

// 

bool Board::isMove(int piece,int rotation, int px, int py) {
	for (int i = px, i1=0; i < px + 4; i++, i1++) {
		for (int j = py, j1 = 0; j < py + 4; j++, j1++) {
			if (inside(i, j)) {
				if (pPiece->GetBlockType(piece, rotation, i1, j1) != 0)
					return false;
			}
			if (j1 >= 0)
			{
				if ((pPiece->GetBlockType(piece, rotation, i1, j1) != 0) &&
					(board[i][j] != 0))
					return false;
			}
		}
	}
	return true;
}
 

