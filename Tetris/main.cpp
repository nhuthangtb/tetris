//#include <iostream>
//#include "Board.h"
#include "Piece.h"
#include "Game.h"
#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{

	
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init";
		return -1;
	}
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return -1;
	}

	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screen;
	SDL_Event e;
	Piece piece;
	Board board(&piece);

	
	SDL_CreateWindowAndRenderer(400, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window, &renderer);
	
	Game game(&piece, &board, renderer);
	
	game.loop();

 }

