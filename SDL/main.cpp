#include <iostream>
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include "Tile.h"

#define WIDTH 1600
#define HEIGHT 900

#define WIDTH_IMG 1366
#define HEIGHT_IMG 720


#define MARGIN_LEFT 0
#define MARGIN_TOP 0



using namespace std;
/*
int SDL_main(int argc, char* argv[])
{
	SDL_Surface* surf = IMG_Load("134.jpg");
	SDL_Surface* bk_surf = IMG_Load("background.jpg");
	int width = surf->w;
	int height = surf->h;
	int clipPerRow = 16;
	int clipPerColumn = 16;
	SDL_Window* window = SDL_CreateWindow("GG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_Texture* bk_texture = SDL_CreateTextureFromSurface(renderer, bk_surf);
	SDL_FreeSurface(bk_surf);
	SDL_FreeSurface(surf);
	SDL_Texture* clip[16][16];
	for (int i = 0; i < clipPerRow; i++)
	{
		for (int j = 0; j < clipPerColumn; j++)
		{
			clip[i][j] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width / clipPerRow, height / clipPerColumn);
			SDL_SetTextureBlendMode(clip[i][j], SDL_BLENDMODE_BLEND);
			SDL_Rect rect = { i * width / clipPerRow,j * height / clipPerColumn, width / clipPerRow, height / clipPerColumn };
			SDL_SetRenderTarget(renderer, clip[i][j]);
			SDL_RenderCopy(renderer, texture, &rect, NULL);

		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_Event e;
	int quit = 0;
	SDL_Texture* tmp = clip[15][15];
	clip[15][15] = clip[1][1];
	clip[1][1] = tmp;
	while (!quit) {
		while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) quit = 1;
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		SDL_Rect bk_rect = { 0, 0, WIDTH, HEIGHT};
		SDL_RenderCopy(renderer, bk_texture, NULL, &bk_rect);

		for (int i = 0; i < clipPerRow; i++)
		{
			for (int j = 0; j < clipPerColumn; j++)
			{
				//SDL_Rect rect = { MARGIN_LEFT + i * width / clipPerRow, MARGIN_TOP + j * height / clipPerColumn, width / clipPerRow, height / clipPerColumn };
				SDL_Rect rect = { MARGIN_LEFT + i * (WIDTH_IMG / clipPerRow), MARGIN_TOP + j * (HEIGHT_IMG / clipPerColumn), WIDTH_IMG / clipPerRow, HEIGHT_IMG / clipPerColumn };
				SDL_RenderCopy(renderer, clip[i][j], NULL, &rect);
			}
		}
		SDL_RenderPresent(renderer);
	}
	return 0;
}
*/

int SDL_main(int argc, char* argv[])
{
	Tile Game;
	SDL_Event e;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				Game.Button(e.motion.x, e.motion.x);
				break;
			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				break;
			case SDL_QUIT:
					quit = true;
					break;
			}
		}
		
		//SDL_RenderPresent(renderer);
	}
	return 0;
}