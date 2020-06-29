#ifndef TILE_H
#define TILE_H
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#define WIDTH 1600
#define HEIGTH 900

#define WIDTH_IMG 1600
#define HEIGTH_IMG 900

#define MARGIN_LEFT 10
#define MARGIN_TOP 10

#define MAX_CELLS 10

#undef main

using namespace std;
class Tile
{
private:
	SDL_Window* window{ nullptr };
	SDL_Color col;
	SDL_Rect dest;
	SDL_Rect window_rect;
	SDL_Renderer* renderer;
	SDL_Texture* background = nullptr;
	SDL_Texture* clip[MAX_CELLS][MAX_CELLS];
	SDL_Texture* T_IMG_1;
	SDL_Texture* T_IMG_2;
	SDL_Texture* T_IMG_3;
	SDL_Texture* T_IMG_4;
public:
	Tile();
	~Tile();
	void init();
	void Button(int x, int y);
};
#endif
