#include "Board.h"
#include "Piece.h"
#include "SDL_mixer.h"

#include <iostream>
using namespace std;
Board::Board(Piece* piece) {
	this->pPiece = piece;
	this->score = 0;
	initBoard();
}


void Board::initBoard() {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (i == 0 || i == WIDTH -1 || j == HEIGHT-1) this->board[i][j] = 1;
			else board[i][j] = 0;
		}
	}
}

void Board::savePiece(int type, int angle, int px, int py) {
	for (int i1 = px, i2 = 0; i1 < px + 4; i1++, i2++) {
		for (int j1 = py, j2 = 0; j1 < py + 4; j1++, j2++) {
			if (pPiece->getBlock(type, angle, i2, j2) == 1) {
				board[i1][j1] = 1;

			}
		}
	}
	
	
}

void Board::deleteLine(int py) {
	
	for (int y = py - 1; y > 0; y--) {
		for (int x = 1; x < WIDTH - 1; x++) {
			this->board[x][y + 1] = this->board[x][y];
		}
	}
	for (int x = 1; x < WIDTH-1; x++) {
		this->board[x][0] = 0;
	}
}

void Board::deletePossibleLine() {
	for (int i = HEIGHT - 2; i >= 0; i--) {
		bool check = true;
		for (int j = 1; j < WIDTH - 1; j++) {
			if (this->board[j][i] == 0) {
				check = false;
				break;
			}
		}
		if (check == true) {
			deleteLine(i);
			score++;
			i++;
		}
	}	
}

bool Board::isBlock(int px, int py) {
	if (board[px][py] == 1) return true;
	else return false;
}

bool Board::isColission(int type, int angle, int px, int py) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pPiece->getBlock(type, angle, i, j) != 0) {
				int x = px + i;
				int y = py  + j;
				if (x <= 0 || x >= WIDTH - 1 || y < 0 || y >= HEIGHT - 1) return true;
				if (board[x][y] == 1) return true;

			}
		}
		
	}
	return false;
}

bool Board::isGameOver() {
	for (int i = 1; i < WIDTH-1; i++) {
		if (board[i][0] == 1) return true;
	}
	return false;
}