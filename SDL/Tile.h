#ifndef TILE_H
#define TILE_H
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#define WIDTH 1600
#define HEIGTH 900

#define WIDTH_IMG 1366
#define HEIGTH_IMG 720

#define MARGIN_LEFT 10
#define MARGIN_TOP 10

#define MAX_CELLS 10

#undef main

using namespace std;

enum State
{
	choose_img,
	choose_cells,
	game,
	win
};

class Tile
{
private:
	State Game_State;
	SDL_Window* window{ nullptr };
	SDL_Color col;
	SDL_Rect dest;
	SDL_Rect window_rect;
	SDL_Renderer* renderer;
	SDL_Texture* background = nullptr;
	int cells_x;
	int cells_y;
	SDL_Texture*** clip;
	SDL_Texture*** clip_for_check;
	//SDL_Texture* clip[MAX_CELLS][MAX_CELLS];
	//SDL_Texture* clip_for_check[MAX_CELLS][MAX_CELLS];
	SDL_Surface* Surf_Target_IMG;
	SDL_Surface* IMG_1;
	SDL_Surface* IMG_2;
	SDL_Surface* IMG_3;
	SDL_Surface* IMG_4;
	SDL_Texture* Target_IMG;
	SDL_Texture* T_IMG_1;
	SDL_Texture* T_IMG_2;
	SDL_Texture* T_IMG_3;
	SDL_Texture* T_IMG_4;
	void Draw_Start();
	void Draw_Cels();
	void Draw_Game();
public:
	Tile();
	~Tile();
	void init();
	void Button_Click(int x, int y);
	void Button_Mov(int x, int y);
	void Draw();
	SDL_Renderer* Get_renderer();
};
#endif
