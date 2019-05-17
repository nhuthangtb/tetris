#pragma once

#include "Board.h"
#include "Piece.h"
#include "SDL_ttf.h"
#include <SDL.h>
#include<string>
using namespace std;
class Game {
public:
	Game(Piece* pPiece, Board* pBoard, SDL_Renderer *renderer);
	void initGame();
	void drawBoard();
	void drawPiece(int type, int angle, int px, int py);
	void drawText(std::string content, int x, int y, int xx, int yy);
	void createNewPiece();
	int cPx, cPy, cType, cAngle;
	int score;
	Uint32 moveTime;
	void loop();

private:
	
	int nPx, nPy, nType, nAngle;
	Piece* pPiece;
	Board* pBoard;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font;
};
