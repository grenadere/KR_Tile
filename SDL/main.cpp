#include <iostream>
#include <SDL.h>
#undef main
#include <SDL_image.h>

#define WIDTH 1600
#define HEIGHT 900

#define MARGIN_LEFT 10
#define MARGIN_TOP 10

using namespace std;

int SDL_main(int argc, char* argv[])
{
	SDL_Surface* surf = IMG_Load("134.jpg");
	int width = surf->w;
	int height = surf->h;
	int clipPerRow = 16;
	int clipPerColumn = 16;
	SDL_Window* window = SDL_CreateWindow("GG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
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
	while (!quit) {
		while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) quit = 1;
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		for (int i = 0; i < clipPerRow; i++)
		{
			for (int j = 0; j < clipPerColumn; j++)
			{
				SDL_Rect rect = { MARGIN_LEFT + i * width / clipPerRow, MARGIN_TOP + j * height / clipPerColumn, width / clipPerRow, height / clipPerColumn };
				SDL_RenderCopy(renderer, clip[i][j], NULL, &rect);
			}
		}
		SDL_RenderPresent(renderer);
	}
	return 0;
}