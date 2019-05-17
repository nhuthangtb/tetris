#pragma once
#include "Piece.h"
#define WIDTH 10
#define HEIGHT 20
class Board {
public:
	
	Board(Piece* piece);
	
	void initBoard();
	void savePiece(int type, int angle,int px, int py);
	void deleteLine(int PY);
	void deletePossibleLine();
	bool isBlock(int px, int py);
	bool isColission(int type, int angle, int px, int py) ;
	bool isGameOver();
	int getScore() { return this->score; } 
private:
	int score;
	int board[WIDTH][HEIGHT];
	Piece* pPiece;
};
