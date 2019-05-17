#include <SDL.h>
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include "SDL_mixer.h"
#include <iostream>
#include <SDL_ttf.h>
#include <sstream>



Game::Game(Piece* pPiece, Board* pBoard, SDL_Renderer* renderer) {
	this->pPiece = pPiece;
	this->pBoard = pBoard;
	this->renderer = renderer;
	
	initGame();
}

void Game::initGame() {
	srand(time(NULL));
	cType = rand() % 6;
	cAngle = rand() % 3 ;
	cPx = 4;
	cPy = -1;

	nType = rand() % 6;
	nAngle = rand() % 3;
	nPx = WIDTH + 2;
	nPy = HEIGHT - 10;

}

void Game::drawBoard() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (pBoard->isBlock(i, j)) {				
				SDL_Rect rect{ i * 25, j * 25, 24, 24 };
				SDL_RenderFillRect(this->renderer, &rect);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::drawPiece(int type, int angle,int px, int py) {
	if(type == 1 ) SDL_SetRenderDrawColor(renderer, 0x00, 0x7f, 0x7f, 0xff);
	else if(type==2)SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pPiece->getBlock(type, angle, i, j) == 1) {
				SDL_Rect rect{ (px+i) * 25,(py+j) * 25, 24, 24 };
				SDL_RenderFillRect(this->renderer, &rect);
			}
		}
	}
}

void Game::createNewPiece() {
	srand(time(NULL));
	cType = nType;
	cAngle = nAngle;
	cPx = 3;
	cPy = -1;

	nType = rand() % 7;
	nAngle = rand() % 3;
	nPx = WIDTH + 2;
	nPy = HEIGHT - 10;
}

void Game::drawText(std::string content, int x, int y, int xx, int yy){
	
	font = TTF_OpenFont("VeraMoBd.ttf", 20);

	SDL_Color color = {255,255,255 };


	surface = TTF_RenderText_Solid(font, content.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect srcRest;
	SDL_Rect desRect;
	TTF_SizeText(font, content.c_str(), &srcRest.w, &srcRest.h);

	srcRest.x = x;
	srcRest.y = y;

	desRect.x = xx;
	desRect.y = yy;

	desRect.w = srcRest.w;
	desRect.h = srcRest.h;

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
}

void Game::loop() {
	bool isRunning = true;
	SDL_Event e;
	font = TTF_OpenFont("VeraMoBd.ttf", 20); 
		
	while (isRunning) {
		
		if (SDL_WaitEventTimeout(&e, 500)) {
			switch (e.type) {
			case SDL_QUIT: {
				isRunning = false;
				break;
			}
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_UP: {
						if (!pBoard->isColission(cType, (cAngle + 1) % 4, cPx, cPy)) {
							cAngle = (cAngle + 1) % 4;
						}
						break;
					}
					case SDLK_RIGHT: {
						if (!pBoard->isColission(cType, cAngle, cPx + 1, cPy))
							cPx++;
						
						break;
					}
					case SDLK_LEFT: {
						if (!pBoard->isColission(cType, cAngle, cPx - 1, cPy))
							cPx--;
						break;
					}
					case SDLK_DOWN: {
						if (!pBoard->isColission(cType, cAngle, cPx, cPy + 1))
							cPy++;
						break;
					}
				}
			}

		}
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
		SDL_RenderClear(renderer);
		drawBoard();
		drawPiece(cType, cAngle, cPx, cPy);
		drawPiece(nType, nAngle, nPx, nPy);
		//Text tScore;
		drawText( "Score", 0, 0, 300, 180);
		std::string score;
		std::stringstream ss;
		ss << pBoard->getScore();
		score = ss.str();
		
		drawText(score, 0, 0, 300, 200);
		/*Text text;
		drawText(text, text.toString(pBoard->getScore()), 0, 0, 300, 200);*/
		if (SDL_GetTicks() > moveTime) {
			
			moveTime += 600;
			
			if (!pBoard->isColission(cType, cAngle, cPx, cPy + 1))
				cPy++;
			else {
				pBoard->savePiece(cType, cAngle, cPx, cPy);
				pBoard->deletePossibleLine();
				if (pBoard->isGameOver()==true) {
					
					break;
				}
				
				createNewPiece();
				
			}
		}
		
		SDL_RenderPresent(renderer);
	}


}

//int Game::showMenu(SDL_Surface* surface,TTF_Font* font) {
//	Uint32 time;
//	int x, y;
//	const int NUMMENU = 2;
//	const char* labels[NUMMENU] = { "Continue", "Exit" };
//	SDL_Surface* menus[NUMMENU];
//	bool selected[NUMMENU] = { 0,0 };
//	SDL_Color color[2] = { {255,255,255},{255,0,0} };
//	menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
//	menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
//	SDL_Rect pos[NUMMENU];
//	pos[0].x = surface->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
//	pos[0].y = surface->clip_rect.h / 2 - menus[0]->clip_rect.h;
//	pos[1].x = surface->clip_rect.w / 2 - menus[1]->clip_rect.w / 2;
//	pos[1].y = surface->clip_rect.h / 2 - menus[1]->clip_rect.h;
//	SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
//	SDL_Event event;
//	while (true) {
//		time = SDL_GetTicks();
//		while (SDL_PollEvent(&event)) {
//			switch (event.type) {
//			case SDL_QUIT:
//				for (int i = 0; i < NUMMENU; i++)
//					SDL_FreeSurface(menus[i]);
//				return 1;
//			case SDL_MOUSEMOTION:
//				x = event.motion.x;
//				y = event.motion.y;
//				for (int i = 0; i < NUMMENU; i++) {
//					if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
//						y >= pos[i].y && y < pos[i].y + pos[i].h) {
//						if (!selected) {
//							selected[i] = true;
//							SDL_FreeSurface(menus[i]);
//							menus[i] = TTF_RenderText_Solid(font, labels[i] , color[1]);
//						}
//						else {
//							if (selected[i]) {
//								selected[i] = false;
//								SDL_FreeSurface(menus[i]);
//								menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
//							}
//						}
//					}
//				}
//			case SDL_MOUSEBUTTONDOWN:
//				x = event.button.x;
//				y = event.button.y;
//				for (int i = 0; i < NUMMENU; i++) {
//					if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
//						y >= pos[i].y && y < pos[i].y + pos[i].h) {
//						for (int j = 0; j < NUMMENU; j++)
//							SDL_FreeSurface(menus[j]);
//						return i;
//					}
//						
//					break;
//				}
//			case SDL_KEYDOWN:
//				if (event.key.keysym.sym == SDLK_ESCAPE) {
//					for (int i = 0; i < NUMMENU; i++)
//						SDL_FreeSurface(menus[i]);
//					return 0;
//				}
//				
//			}
//			
//
//		}
//	}
//
//	
//}