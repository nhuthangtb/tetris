#pragma once


#include "Pieces.h"
class Board {
public:
	void createBoard();
	void displayBoard();
	bool isGameOver();
	void removeLine(int py);
	void removeAllLines();
	void drawPiece(int piece, int rotation, int px, int py);
	int left(int px, int py);
	int right(int px, int py);
	int down(int px, int py);
	bool inside(int px, int py);
	bool isMove(int piece, int rotation, int px, int py);
private:
	Pieces *pPiece;
};
